#include "GedApp.hpp"

#include <SDL2/SDL.h>
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
//    LOG(TRACE) << "Initializing SDL.";

    /* Initialize defaults, Video and Audio */
    // if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        String msg = getSdlErrorMsg("SDL_Init failed");
        throw Exception(msg);
    }

//    LOG(TRACE) << "SDL initialized.";
}

int GedApp::runApp() {
    try {
        GedWindow win;

//        LOG(TRACE) << "Pre win.createWindow().";
        win.createWindow();
//        LOG(TRACE) << "Pre win.show().";
        win.show();
//        LOG(TRACE) << "Pre event loop().";

        App::runApp();

    } catch (Exception &e) {
        LOG(INFO) << "SQL_Quit";
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

// String GedApp::getSdlErrorMsg(String msgPrefix) {
//     String error = SDL_GetError();
//     String msg = format("%sError(%s)", msgPrefix, error);
//     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SdlWin Error", msg.c_str(), nullptr);

//     return msg;
// }

void GedApp::onQuit(QuitEvent &event) {
    UNUSED(event);
    LOG(INFO) << "GedApp::onQuit event)";
    LOG(INFO) << "Quiting SDL.";

    /* Shutdown all subsystems */
    SDL_Quit();
}
