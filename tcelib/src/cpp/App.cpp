#include "App.hpp"

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
