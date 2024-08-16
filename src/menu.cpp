#include "menu.h"
#include "util.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>


#include <vector>
#include <string>
#include <functional>
///*


void menu::refresh(){
    if (!started) return;
    for(int i=0; i<this->noOpts; i++)
        drawEntry(i, i == this->highOpt);
}

void menu::drawEntry(int i, bool highlighted){
    if (!started) return;
    SDL_Surface* tmp = TTF_RenderText_Solid_Wrapped(this->font, this->optsVec[i].c_str(), highlighted ? this->highlightColor : this->normalColor, this->pos.w);
    SDL_Texture* _tmp = SDL_CreateTextureFromSurface(this->renderer, tmp);
    SDL_RenderCopy(this->renderer, _tmp, NULL, &entryPosVec.at(i));
    SDL_FreeSurface(tmp);
    SDL_DestroyTexture(_tmp);
}


void menu::handleEvent(SDL_Event* e){
    if(!started) return;
    switch(e->type){
        case SDL_MOUSEMOTION:
            if(mouseMotionInRect(&e->motion, &this->pos)){
                bool f = false, found = false;
                for(int i=0; i<this->noOpts; i++){
                    f = mouseMotionInRect(&e->motion, &entryPosVec.at(i));
                    if(f) {
                        this->highOpt = i;
                        found = true;
                    }
                } if (not found) this->highOpt = -1;
            } else this->highOpt = -1;
        break;
        case SDL_MOUSEBUTTONDOWN:
            if(e->button.button == 1){
                for (int i=0; i<this->noOpts; i++) {
                    if (inRect(e->button.x, e->button.y, &entryPosVec.at(i))) {
                        callsVec.at(i)();
                        break;
                    }
                }
            }
        break;
        case SDL_CONTROLLERBUTTONDOWN:
            switch(e->cbutton.button){
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                if(this->highOpt == -1) this->highOpt = 0;
                else if(this->highOpt < this->noOpts) this->highOpt++;
            break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                if(this->highOpt == -1) this->highOpt = this->noOpts;
                else if(this->highOpt > 0) this->highOpt--;
            break;
            case SDL_CONTROLLER_BUTTON_A:
                this->callsVec.at(highOpt)();
            break;
            }
        break;
    }
}

void menu::start(){
    SDL_RenderCopy(this->renderer, this->bg, NULL, &this->pos);
    int vstep = this->pos.h / this->noOpts;
    SDL_Surface* tmp;
    SDL_Texture* _tmp;
    SDL_Rect entryPos = {
            this->pos.x,
            0,
            this->pos.w,
            vstep
    };
    for(int i=0; i<this->noOpts; i++){
        SDL_Surface* tmp = TTF_RenderText_Solid_Wrapped(this->font, this->optsVec[i].c_str(), this->normalColor, this->pos.w);

        entryPos.x = this->pos.x + (this->pos.w - tmp->w) / 2;
        entryPos.y = this->pos.y + i * vstep;
        if(tmp->w > this->pos.w) tmp->w = this->pos.w;
        entryPos.w = tmp->w;

        SDL_FreeSurface(tmp);
        this->entryPosVec.push_back(entryPos);
        this->drawEntry(i, false);
    }
    this->started = true;

}
void menu::stop(){
    this->started = false;
}

menu::menu(int _noOpts, SDL_Rect _pos, SDL_Renderer *_renderer, TTF_Font *_font, std::vector<std::string> _optsVec, std::vector<std::function<void()>> _callsVec, SDL_Texture *_bg, SDL_Color _normalColor, SDL_Color _highlightColor, SDL_Color _bgcolor){
    this->noOpts = _noOpts;
    this->highOpt = -1;
    this->pos = _pos;
    this->renderer = _renderer;
    this->font = _font;
    this->normalColor = _normalColor;
    this->highlightColor = _highlightColor;
    this->optsVec = _optsVec;
    this->callsVec = _callsVec;
    this->started = false;
    this->entryPosVec = std::vector<SDL_Rect>();

    if(_bg == NULL) {
        SDL_BlendMode oldMode;
        SDL_GetRenderDrawBlendMode(this->renderer, &oldMode);
        SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);


        this->bg = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, this->pos.w, this->pos.h);
        SDL_SetTextureBlendMode(this->bg, SDL_BLENDMODE_BLEND);
        
        uint32_t* pixels = (uint32_t*) malloc(this->pos.h * this->pos.w * 4);
        uint32_t pixel = PIXEL(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
        for(int i = 0; i < this->pos.w * this->pos.h; i++) {
            *(pixels + i) = pixel;
        }
        SDL_UpdateTexture(this->bg, NULL, pixels, this->pos.w);

        SDL_SetRenderDrawBlendMode(renderer, oldMode);
    } else this->bg = _bg;

}