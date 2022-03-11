#include "App.hpp"

#include "Window.hpp"

#include "easylogging++.h"

App *App::app = nullptr;

App::App() {
    id = NULL;
    registerEventHandling();
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

// void App::onShown(WindowEvent &event) {
//     LOG(INFO) << "Received the App::onShown event";
// }