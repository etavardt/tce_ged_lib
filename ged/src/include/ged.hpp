#pragma once

#include <iostream>
#include "App.hpp"

using namespace std;

class GedApp : public App {
public:
    static GedApp &getInstance();
    static GedApp &getApp() { return gedApp; }
    static GedApp &gedApp;

    int runApp() override { cout << "Hello World" << endl; return 0; }
    int processCmdLine(int argCnt, char **argList) override { return 0; }
};
