#include "level.h"
#include "util.h"

#include <ctime>
#include <cstdlib>
#include <thread>
#include <vector>
#include <limits.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#define NUMPLATFORMS 10


level::level(levelConfig* _conf){
    this->conf = _conf;
    srand(time(NULL));
    this->tick = false;
}

void level::handOver(){
    this->running = true;
    int screenW, screenH, vSpeed = 0;
    SDL_GetWindowSizeInPixels(SDL_RenderGetWindow(this->conf->renderer), &screenW, &screenH);
    this->player = {100, screenH/2, 40, 80};
    SDL_Event e;

    this->platforms = std::vector<SDL_Rect*>();
    SDL_Rect first = {0, screenH/2 + 150, 200, 40};
    this->platforms.push_back(&first);
    SDL_Rect* _tmp;
    int lastX = first.x + first.w, lastY = first.y;
    for(int i=0; i<NUMPLATFORMS - 1; i++){
        _tmp = new SDL_Rect();
        makePlatform(lastX, lastY, screenH, _tmp);
        lastX = _tmp->x + _tmp->w;
        lastY = _tmp->y;
        this->platforms.push_back(_tmp);
    }


    std::thread ticker = std::thread(&level::_tick, this);
    int platIndex, platFirst;
    while(this->running){
        if(this->tick){
            
            for(int i=0; i<NUMPLATFORMS; i++){
                this->platforms.at(i)->x -= this->conf->hSpeed;
                if(this->platforms.at(i)->x + this->platforms.at(i)->w < 0){
                    SDL_Rect* prevPlatform = i == 0 ? this->platforms.at(NUMPLATFORMS - 1) : this->platforms.at(i - 1);
                    this->makePlatform(prevPlatform->x + prevPlatform->w, prevPlatform->y, screenH, this->platforms.at(i));                    
                }
            }



            vSpeed += this->conf->gravity;
            if (vSpeed > this->conf->speedCap) vSpeed = this->conf->speedCap;
            else if (vSpeed < -this->conf->speedCap) vSpeed = -this->conf->speedCap;
            platIndex = this->getTouchingPlatform();
            if(platIndex != -1) {
                if (vSpeed > 0) vSpeed = 0;
                if(this->player.y > this->platforms.at(platIndex)->y) this->player.y = this->platforms.at(platIndex)->y;
            }
            this->player.y += vSpeed;


            if (this->player.y > screenH){
                //printf("Game over\n");
                this->player.y = screenH / 2;
                vSpeed = 0;
            }

            SDL_RenderClear(this->conf->renderer);
            SDL_RenderCopy(this->conf->renderer, this->conf->bg, NULL, NULL);
            SDL_RenderCopy(this->conf->renderer, this->conf->player, NULL, &player);
            for(int i=0; i<NUMPLATFORMS; i++){
                //printf("Rendering index %d at %d, %d; %dx%d\n", i, platforms.at(i)->x, platforms.at(i)->y, platforms.at(i)->w, platforms.at(i)->h);
                SDL_RenderCopy(this->conf->renderer, this->conf->platform, NULL, platforms.at(i));
            }

            SDL_RenderPresent(this->conf->renderer);
            this->tick = false;
        }
        while(SDL_PollEvent(&e)){
            switch (e.type){
                case SDL_CONTROLLERBUTTONDOWN:
                    switch (e.cbutton.button){
                        case SDL_CONTROLLER_BUTTON_B:
                            this->stop(&ticker);
                        break;
                        case SDL_CONTROLLER_BUTTON_A:
                            if(this->getTouchingPlatform() != -1){
                                vSpeed -= this->conf->jumpForce;
                            }
                        break;
                    }
                break;
                case SDL_QUIT:
                    this->stop(&ticker);
                break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.scancode){
                        case SDL_SCANCODE_SPACE:
                            if(this->getTouchingPlatform() != -1){
                                vSpeed -= this->conf->jumpForce;
                            }
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            this->stop(&ticker);

                    default:
                        break;
                    }
                break;
            }
        }
    }
}

void level::_tick(){
    while (this->running){
        this->tick = true;
        std::this_thread::sleep_for(std::chrono::nanoseconds(this->conf->speedNs));
    }
    
}

void level::stop(std::thread* ticker){
    ticker->detach();
    this->running = false;
}

int level::getTouchingPlatform(){
    for(int i = 0; i < NUMPLATFORMS; i++){
        if(SDL_HasIntersection(&this->player, this->platforms.at(i)) == SDL_TRUE) return i;
    }
    return -1;
}

void level::makePlatform(int lastX, int lastY, int screenH, SDL_Rect* platform){
    platform->y = lastY + RANDTO(this->conf->maxHeightDelta);
    if (platform->y > screenH - this->conf->maxHeightDelta) platform->y = screenH - this->conf->maxHeightDelta;
    else if (platform->y < this->conf->maxHeightDelta) platform->y = this->conf->maxHeightDelta;
    platform->x = lastX + this->conf->spacing;
    platform->w = this->conf->minPlatformLength + RANDTO(this->conf->maxPlatformLength - this->conf->minPlatformLength);
    platform->h = 40;
}
