#ifndef __MENU_H
#define __MENU_H
 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <functional>


class menu{
private:
    int noOpts, highOpt;
    bool started;
    SDL_Rect pos;
    SDL_Color normalColor, highlightColor;
    SDL_Renderer* renderer;
    SDL_Texture* bg;
    TTF_Font* font;
    std::vector<std::string> optsVec;
    std::vector<std::function<void()>> callsVec;
    std::vector<SDL_Rect> entryPosVec;
    void drawEntry(int i, bool highlighted = false);
public:
    void handleEvent(SDL_Event* e);
    void start();
    void stop();
    void refresh();
    menu(int _noOpts, SDL_Rect _pos, SDL_Renderer *_renderer, TTF_Font *_font, std::vector<std::string> _optsVec, std::vector<std::function<void()>> _callsVec, SDL_Texture *_bg = NULL, SDL_Color _normalColor = {0, 0, 0, 0}, SDL_Color _highlightColor = {0, 255, 0, 0}, SDL_Color _bgcolor = {0, 0, 0, 0});    
};



#endif