#include "App.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Window.hpp"
#include "Exception.hpp"

#include "easylogging++.h"

App *App::app = nullptr;

App::App() {
    id = 0;
    registerEventHandling();
}

App::~App() {
    unRegisterEventHandling();
}

void App::init() {
    /* Initialize defaults, Video and Audio */
    // if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)) {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        String msg = getSdlErrorMsg("Error initializing SDL: ");
        throw Exception(msg);
    }

    if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
        String msg = getSdlErrorMsg("Error initializing SDL_image: ");
        throw Exception(msg);
    }

    // Initialize SDL_ttf
    if ( TTF_Init() < 0 ) {
        String msg = getSdlErrorMsg("Error intializing SDL_ttf: ");
        throw Exception(msg);
    }
}

App &App::getApp() {
    if (app == nullptr) throw "No Application Object Exists";
    return *app;
}

int App::runApp() {
    processEventLoop();
    return 1;
}

void App::processEventLoop() {
    while (EventHandler::pollEvent()) {
        // TODO: Timing and Graphics processing.
    };
}
