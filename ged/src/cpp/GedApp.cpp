#include "GedApp.hpp"

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
    App::init(); // default SDL Subsystems Initialized Generically

    // TODO: Handle more that one font?
    font = TTF_OpenFont("fonts/arial.ttf", 25);
    if (font == nullptr) {
        String msg = getSdlErrorMsg("TTF_OpenFont failed");
        throw Exception(msg);
    }
}

int GedApp::runApp() {
    GedWindow win;

    win.createWindow();
    win.show();

    App::runApp();

    return 0;
}

int GedApp::processCmdLine(int argCnt, char **argList) {
    App::processCmdLine(argCnt, argList);
    return 1;
}

void GedApp::onQuit(QuitEvent &event) {
    UNUSED(event);
    LOG(INFO) << "GedApp::onQuit event)";
}
