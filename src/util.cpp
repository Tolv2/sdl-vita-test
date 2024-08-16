#include "util.h"

#include <SDL2/SDL.h>

#include <cstdio>
#include <string.h>
#include <cerrno>
#include <iostream>
#include <string>
#include <vector>



#ifdef __VITA
#include <psp2/sysmodule.h>
#include <psp2/net/net.h> 
#include <psp2/kernel/clib.h>
#include <psp2/kernel/threadmgr.h>
int debug_socket_fd;
int initOutput(){
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);

	SceNetInitParam net_init_param;
    net_init_param.memory = malloc(NET_SIZE);
    net_init_param.size = NET_SIZE;
    net_init_param.flags = 0;
    if (sceNetInit(&net_init_param) < 0) {
        sceKernelDelayThread(5 * SECOND);
		return -1;
    }
    debug_socket_fd = networkSocket(SERVER_IP, SERVER_PORT);
    return 0;
}

int networkSocket(const char* address, int port){
	int sfd = sceNetSocket("stdout-socket", SCE_NET_AF_INET, SCE_NET_SOCK_STREAM, 0);

	if(sfd < 0) {
		return -2;
	}

	SceNetSockaddrIn server_addr = {0};

	server_addr.sin_family = SCE_NET_AF_INET;
	server_addr.sin_port = sceNetHtons(port);

	if (sceNetInetPton(SCE_NET_AF_INET, address, &(server_addr.sin_addr.s_addr)) < 0) {
        return -3;
    }

	SceNetSockaddr *name = (SceNetSockaddr *) &server_addr;

	if (sceNetConnect(sfd, name, sizeof(server_addr)) < 0) {
		return -4;
	}
	return sfd;
}

int printf(const char* fmt, ...){
	char msgbuf[MAX_MSG_SIZE] = {0};
	va_list argptr;
	va_start(argptr, fmt);
	int ret = sceClibVsnprintf(msgbuf, MAX_MSG_SIZE, fmt, argptr);
	va_end(argptr);
	sendDebugOutput(msgbuf);
	return ret;
}

int print(const char* msg){
	return printf("%s", msg);
}
int sendDebugOutput(const char* message){
	return sceNetSend(debug_socket_fd, message, sceClibStrnlen(message, MAX_MSG_SIZE), 0);
}

void sendOutput(const char* message, int sfd) {
	sceNetSend(sfd, message, sceClibStrnlen(message, MAX_MSG_SIZE), 0);
}

#else 
int initOutput(){
        return 0;
    }
#endif


void myErr(const char * s, std::ostream* stream){
#ifdef __VITA
    printf("Internal error: %s\nErrno %d; %s\nSDL error: %s\n", s, errno, strerror(errno), SDL_GetError());
#else
    *(stream) << "Internal error: " << s << "\nErrno: " << errno << "; " << strerror(errno) << "\nSDL error: " << SDL_GetError() << '\n';
#endif
}

std::vector<std::string> split(std::string const &s, char const* const delim) {
    std::vector<std::string> ret;
    std::string strDelim = std::string(delim);
    std::string tmp;
    int i = 0, j;
    do{
        j = s.find(delim, i);
        ret.push_back(s.substr(i, j - i));
        tmp = s.substr(j + 1);
        if (!strContains(&tmp, &strDelim))
            ret.push_back(tmp);
        i = j + 1;
    } while (strContains(&tmp, &strDelim));
    return ret; 
}

std::string vectostr(std::vector<std::string> const &s) {
    std::string out = std::string();
    for(int i=0; i<s.size(); i++){
        out.append(s[i] + ", ");
    }
    return out;
}

bool inRect(int x, int y, SDL_Rect* rect) {
    return  (x >= rect->x && x < (rect->x + rect->w)) &&  (y >= rect->y && y < (rect->y + rect->h));
}

bool mouseMotionInRect(SDL_MouseMotionEvent* mme, SDL_Rect* rect){
    return inRect(mme->x, mme->y, rect);
}

SDL_GameController *findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            SDL_GameControllerOpen(i);
        }
    }

    return NULL;
}


bool strContains(std::string* lookingIn, std::string* lookingFor){
    int foundLen = 0, targetLen = lookingFor->length();
    for(int i = 0; i < lookingIn->length(); i++){
        if(lookingIn->at(i) == lookingFor->at(foundLen)) {
            foundLen ++;
        }
        else {
            foundLen = 0;
        }
        if (foundLen == targetLen) {
            return true;
        }
    }
    return false;
}