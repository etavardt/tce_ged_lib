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

//    String getSdlErrorMsg(String msgPrefix);

    void onQuit(QuitEvent &event) override;
};
