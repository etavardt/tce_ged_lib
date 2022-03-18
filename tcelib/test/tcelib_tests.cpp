#include <gtest/gtest.h>

#include "App.hpp"
#include "easylogging++.h"

class MyApp : public App {
public:
    static MyApp &getInstance();
    static MyApp &getApp() { return myApp; }
    static MyApp &myApp;

    void init() override {}
    int runApp() override { return 0; }
    int processCmdLine(int argCnt, char **argList) override { return 0; }
};

MyApp& MyApp::myApp = MyApp::getInstance();

MyApp &MyApp::getInstance() {
    static MyApp instance;
    app = &instance;
    return instance;
}

INITIALIZE_EASYLOGGINGPP

TEST(tcelibTest, singletonCheck) {
    App &app = App::getApp();
    EXPECT_NE(&app, nullptr); // Bob should already be created

    MyApp *instance = &MyApp::getInstance();
    EXPECT_EQ(instance, &app); // Testing of getInstance function

    MyApp *myApp1 = static_cast<MyApp *>(&app);
    EXPECT_EQ(myApp1, &app); // Testing of getApp virtual function

    MyApp *myApp2 = &MyApp::getApp();
    EXPECT_EQ(myApp2, myApp1); // Retesting of getApp using child class
}
