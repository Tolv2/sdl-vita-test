#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
#include <chrono>
#include <map>

#include "util.h"
#include "menu.h"
#include "level.h"

#define WIDTH 960
#define HEIGHT 544
#define FRAME_TIME_MS 16
#define FRAME_TIME_NS 16666666


const int fileNumber = 4;
const char* fileList[fileNumber] {"assets/png/player.png", "assets/png/bg.png", "assets/png/platform.png", "assets/png/menu.png"};
const char* fontFile = "assets/ttf/SourceCodePro-Black.ttf";
bool renderFlag = true;
bool killFlag = false;

void update(){
    while(!killFlag){
        renderFlag = true;
        std::this_thread::sleep_for(std::chrono::nanoseconds(FRAME_TIME_NS));
    }
}

int main(void) {

    if(initOutput() != 0){
        exit(-1);
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        myErr("SDL init err");
        return -1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        myErr("SDL IMG init err");
        return -2;
    }
    if (TTF_Init() < 0) {
        myErr("SDL TTF init err");
        return -7;
    }

    SDL_Window* window = SDL_CreateWindow("No wgl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        myErr("Creating window failed");
        return -3;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if (renderer == NULL){
        myErr("Create renderer failed");
        return -4;
    }


    TTF_Font* font = TTF_OpenFont(fontFile, 64);
    if (font == NULL) {
        myErr("Opening font failed!");
        return -5;
    }
    
    
    SDL_Color textColor = {255, 0, 0, 0}, hoverColor = {0, 255, 0, 0}, curColor = textColor;
    SDL_Rect textRect;


    std::map<std::string, SDL_Texture *> textureMap;
    SDL_Surface* s;
    SDL_Texture* t;
    std::string name;


    SDL_GameController* controller = findController();
    if (controller == NULL){
        myErr("Couldn't get controller");
    }

    std::thread ticker = std::thread(update);

    for (int i = 0; i < fileNumber; i++){
        name = split(split(fileList[i], "/").back(), ".").front();
        std::cout << "Now loading: " << name << " (" << fileList[i] << ")...\n";
        s = IMG_Load(fileList[i]);
        if (s == NULL) {
            myErr("Loading texture failed!");
            return -6;
        }
        t = SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
        textureMap[name] = t;
    }

    SDL_Rect menuPos = {0, 0, 600, 200};
    std::vector<std::string> menuOptsVec = std::vector<std::string>();
    std::vector<std::function<void()>> menuCallsVec = std::vector<std::function<void()>>();
    SDL_Color menuNormalColor = {0, 255, 0, 0}, menuHighlightColor = {255, 0, 0, 0};
    
    levelConfig level1conf = {0.8f, 100, FRAME_TIME_NS, 10, 1, 17, 100, 200, 50, 200, textureMap["bg"], textureMap["platform"], textureMap["player"], renderer};

    level level1 = level(&level1conf);

    menuOptsVec.push_back("Gaming");
    menuOptsVec.push_back("Options");
    menuOptsVec.push_back("Quit");

    menuCallsVec.push_back(std::bind(&level::handOver, &level1));
    menuCallsVec.push_back(std::bind(printf, "iks de\n"));
    menuCallsVec.push_back(std::bind(exit, 0));


    menu myMenu = menu(3, menuPos, renderer, font, menuOptsVec, menuCallsVec);
    
    myMenu.start();

    
    while (true){
        if(renderFlag) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textureMap["menu"], NULL, NULL);
            myMenu.refresh();
            SDL_RenderPresent(renderer);
            renderFlag = false;
        }
        SDL_Event e;
        if (SDL_WaitEvent(&e)){
            if (e.type == SDL_QUIT) break;
            
            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONDOWN) {
                myMenu.handleEvent(&e);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
