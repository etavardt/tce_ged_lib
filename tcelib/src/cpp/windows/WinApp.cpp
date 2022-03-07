#include "WinApp.hpp"

App *App::app = nullptr;

App &App::getApp() {
    if (app == nullptr) throw "No Application Object Exists";
    return *app;
}
