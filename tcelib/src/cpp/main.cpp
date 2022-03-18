#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "App.hpp"
#include "Exception.hpp"
#include "easylogging++.h" // 3rd Party Easy Logging++

INITIALIZE_EASYLOGGINGPP

using std::cout;
using std::cerr;
using std::endl;

extern "C"
int main(int ac, char **av) {
    try {
        START_EASYLOGGINGPP(ac, av);

        App &app = App::getApp();
        app.processCmdLine(ac, av);
        app.init();
        app.runApp();
    } catch (Exception &e) {
        LOG(ERROR) << "Exception caught in main: " << e.getMsg() << endl;
    } catch (const std::exception &e) {
        LOG(ERROR) << "std::exception caught in main: " << e.what() << endl;
    } catch (...) {
        LOG(ERROR) << "Unknown Exception caught in main" << endl;
    }

    return 0;
} /* end of main() */
