#include "GedApp.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "easylogging++.h"

#include "String.hpp"
#include "Exception.hpp"
#include "GedWindow.hpp"

#include "unused_macros.hpp"

GedApp& GedApp::gedApp = GedApp::getInstance();

GedApp &GedApp::getInstance() {
    static GedApp instance;
    app = &instance;
    return instance;
}

void GedApp::init() {
    /* Initialize defaults, Video and Audio */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        String msg = getSdlErrorMsg("SDL_Init failed");
        throw Exception(msg);
    }
    if (TTF_Init() != 0) {
        String msg = getSdlErrorMsg("TTF_Init failed");
        throw Exception(msg);
    } else {
        // TODO: Handle more that one font
        font = TTF_OpenFont("fonts/arial.ttf", 25);
        if (font == nullptr) {
            String msg = getSdlErrorMsg("TTF_OpenFont failed");
            throw Exception(msg);
        }
    }
    if (IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP ) == 0) {
        String msg = getSdlErrorMsg("SDL_Init failed: ");
        throw Exception(msg);
    }

}

int GedApp::runApp() {
    try {
        GedWindow win;

        win.createWindow();
        win.show();

        App::runApp();

    } catch (Exception &e) {
        LOG(INFO) << "SQL_Quit";
        TTF_Quit();
        SDL_Quit();
        throw e;
    }
    LOG(INFO) << "Quiting....";
    return 0;
}

int GedApp::processCmdLine(int argCnt, char **argList) {
    App::processCmdLine(argCnt, argList);
    return 1;
}

void GedApp::onQuit(QuitEvent &event) {
    UNUSED(event);
    LOG(INFO) << "GedApp::onQuit event)";
    LOG(INFO) << "Quiting SDL.";

    /* Shutdown all subsystems */
    TTF_Quit();
    SDL_Quit();
}
