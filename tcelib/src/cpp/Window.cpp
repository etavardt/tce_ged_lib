#include "Window.hpp"

#include "App.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "easylogging++.h"

Window::Window() {
}

Window::~Window() {
    //SdlWin::~SdlWin();
    // SDL_DestroyTexture(texture);
    // SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::createWindow() {

    LOG(DEBUG) << "Pre Window.init().";
    init();

    width = desktopDm.w;
    height = desktopDm.h;
    window = SDL_CreateWindow(const_cast<char *>(App::getApp().getAppFileName()),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
                                          SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window != nullptr) {
        id = SDL_GetWindowID(window);
        registerEventHandling();
    } else {
        String msg = getErrorMsg("SDL_Createwindow failed");
        throw Exception(msg);
    }
}

SDL_DisplayMode Window::getDisplayMode(int displayIndex) {
    if(SDL_GetCurrentDisplayMode(displayIndex, &dm) < 0) {
        String msg = getErrorMsg("SDL_GetCurrentDisplayMode failed");
        throw Exception(msg);
    }
}

void Window::init() {
    if(SDL_GetDesktopDisplayMode(0, &desktopDm)) {
        String msg = getErrorMsg("SDL_GetDesktopDisplayMode failed");
        throw Exception(msg);
    };
    getDisplayMode(0);
}

void Window::show() {
    SDL_ShowWindow(window);
}

String Window::getErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%s: Error(%s)", msgPrefix, error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SdlWin Error", msg.c_str(), window);

    return msg;
}

// void Window::onShown(WindowEvent &event) {
//     LOG(INFO) << "Received the Window::onShown event";
// }
// void Window::onClose(WindowEvent &event) {
//     LOG(INFO) << "Received the Window::onClose event";
// }