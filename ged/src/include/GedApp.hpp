#pragma once

#include "App.hpp"
#include "String.hpp"

class GedApp : public App {
  public:
    static GedApp &getInstance();
    static GedApp &getApp() { return gedApp; }
    static GedApp &gedApp;

    int runApp() override;
    int processCmdLine(int argCnt, char **argList) override;

    String getSdlErrorMsg(String msgPrefix);
};
