#ifndef __LEVEL_H
#define __LEVEL_H

#include <SDL2/SDL.h>
#include <vector>
#include <thread>

struct levelConfig{
    float dutyCycle;
    int maxHeightDelta;
    int speedNs;
    int hSpeed;
    int gravity;
    int jumpForce;
    int speedCap;
    int spacing;
    int minPlatformLength;
    int maxPlatformLength;
    SDL_Texture* bg;
    SDL_Texture* platform;
    SDL_Texture* player;
    SDL_Renderer* renderer;
};


class level{
    public:
    level(levelConfig* conf);
    void handOver();
    void stop(std::thread* ticker);



    private:
    levelConfig* conf;
    std::vector<SDL_Rect*> platforms;
    SDL_Rect player;
    bool running;
    bool tick;
    void _tick();
    int getTouchingPlatform();
    void makePlatform(int lastX, int lastY, int screenH, SDL_Rect* platform);
};



#endif