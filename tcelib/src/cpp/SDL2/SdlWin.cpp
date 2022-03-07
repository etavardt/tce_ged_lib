#include "SdlWin.hpp"

#include <SDL2/SDL_messagebox.h>
#include "App.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "easylogging++.h"

SdlWin::SdlWin() {
}

void SdlWin::init() {
    if(SDL_GetDesktopDisplayMode(0, &desktopDm)) {
        String msg = getErrorMsg("SDL_GetDesktopDisplayMode failed");
        throw Exception(msg);
    };
}

//void SdlWin::createWindow(const String title, int x, int y, int w, int h, Uint32 flags) {
void SdlWin::createWindow() {
    width = desktopDm.w;
    height = desktopDm.h;
//    SDL_Window *window = SDL_CreateWindow(title.c_str(),
    window = SDL_CreateWindow(const_cast<char *>(App::getApp().getAppFileName()),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//    LOG(INFO) << format("Post SDL_CreateWindow window = %u.", reinterpret_cast<unsigned long long>(window));
    LOG(INFO) << format("Post SDL_CreateWindow window = %p.", reinterpret_cast<unsigned long long>(window));

    if(window == NULL) {
        String msg = getErrorMsg("SDL_Createwindow failed");
        throw Exception(msg);
    }
}

void SdlWin::getDisplayMode(int displayIndex) {
    if(SDL_GetCurrentDisplayMode(displayIndex, &dm) < 0) {
        String msg = getErrorMsg("SDL_GetCurrentDisplayMode failed");
        throw Exception(msg);
    }
}

void SdlWin::show() {
    SDL_ShowWindow(window);
}

SDL_Event SdlWin::pullEvent() {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
    }

    return event;
}

String SdlWin::getErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%s: Error(%s)", msgPrefix, error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SdlWin Error", msg.c_str(), window);

    return msg;
}