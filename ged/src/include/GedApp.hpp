#pragma once

#include "App.hpp"
#include "String.hpp"

class GedApp : public App {
public:
    static GedApp &gedApp;
    static inline GedApp &getApp() { return gedApp; }
    static GedApp &getInstance();

    void init() override;
    int runApp() override;
    int processCmdLine(int argCnt, char **argList) override;

    void onQuit(QuitEvent &event) override;
};
