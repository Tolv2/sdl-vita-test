#ifndef __MY_UTIL
#define __MY_UTIL

#include <cstdio>
#include <ostream>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#ifdef __VITA
#define NET_SIZE 1024 * 1024
#define MAX_MSG_SIZE 1024
#define SERVER_IP "192.168.1.151"
#define SERVER_PORT 6969
#define SECOND 1000000
int networkSocket(const char* address, int port);
int sendDebugOutput(const char* msg);
void sendOutput(const char* message, int sfd);
#endif

#define PIXEL(r, g, b, a) (r << 24) | (g << 16) | (b << 8) | a
#define RANDTO(x) (int)(x * ((float) rand() / INT_MAX))


void myErr(const char* s, std::ostream* stream = &std::cerr);
int initOutput();

std::vector<std::string> split(std::string const &s, char const* const delim);
std::string vectostr(std::vector<std::string> const &s);

bool inRect(int x, int y, SDL_Rect* rect);
bool mouseMotionInRect(SDL_MouseMotionEvent* mme, SDL_Rect* rect);
SDL_GameController *findController();

bool strContains(std::string* lookingIn, std::string* lookingFor);

#endif