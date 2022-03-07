#include "GedApp.hpp"

#include "easylogging++.h"
#include <SDL2/SDL.h>

#include "String.hpp"
#include "Exception.hpp"
#include "SdlWin.hpp"

GedApp& GedApp::gedApp = GedApp::getInstance();

GedApp &GedApp::getInstance() {
    static GedApp instance;
    app = &instance;
    return instance;
}

int GedApp::runApp() {
    LOG(DEBUG) << "Initializing SDL.";
    throw Exception("Test");
    /* Initialize defaults, Video and Audio */
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)) {
        String msg = getSdlErrorMsg("SDL_Init failed");
        throw Exception(msg);
    }

    LOG(DEBUG) << "SDL initialized.";

    // TODO: Do App Stuff Here!
    SdlWin win;
    LOG(DEBUG) << "Pre win.init().";
    win.init();
    LOG(DEBUG) << "Pre win.createWindow().";
    win.createWindow();
    LOG(DEBUG) << "Pre win.show().";
    win.show();
    LOG(DEBUG) << "Pre event loop().";

    SDL_Event event;
    do {
        event = win.pullEvent();
        switch (event.type) {
        default:
            break;
        };
        // TODO: Timeing and Graphics processing.
    } while (event.type != SDL_QUIT);

    LOG(DEBUG) << "Quiting SDL.\n";

    /* Shutdown all subsystems */
    SDL_Quit();

    LOG(DEBUG) << "Quiting....\n";

    return 0;
}

int GedApp::processCmdLine(int argCnt, char **argList) {
    App::processCmdLine(argCnt, argList);
    return 1;
}


String GedApp::getSdlErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%sError(%s)", msgPrefix, error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SdlWin Error", msg.c_str(), nullptr);

    return msg;
}