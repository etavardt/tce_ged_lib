#include <gtest/gtest.h>

//#include "App.hpp"
#include "easylogging++.h"
#include "GedApp.hpp"
/*
class GedApp : public App {
public:
    static GedApp &getInstance();
    static GedApp &getApp() { return gedApp; }
    static GedApp &gedApp;

    int runApp() override { return 0; }
    int processCmdLine(int argCnt, char **argList) override { return 0; }
};

GedApp& GedApp::gedApp = GedApp::getInstance();

GedApp &GedApp::getInstance() {
    static GedApp instance;
    app = &instance;
    return instance;
}
 */
INITIALIZE_EASYLOGGINGPP

TEST(gedTest, singletonCheck) {
    App &app = App::getApp();
    EXPECT_NE(&app, nullptr); // Bob should already be created

    GedApp *instance = &GedApp::getInstance();
    EXPECT_EQ(instance, &app); // Testing of getInstance function

    GedApp *gedApp1 = static_cast<GedApp *>(&app);
    EXPECT_EQ(gedApp1, &app); // Testing of getApp virtual function

    GedApp *gedApp2 = &GedApp::getApp();
    EXPECT_EQ(gedApp2, gedApp1); // Retesting of getApp using child class
}
