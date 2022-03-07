#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

//#include <windows.h>

#include "WinWinApp.hpp"
#include "Exception.hpp"
#include "easylogging++.h" // 3rd Party Easy Logging++

INITIALIZE_EASYLOGGINGPP

using std::cout;
using std::cerr;
using std::endl;

/*
    hInstance:     is something called a "handle to an instance" or "handle to a module." The operating system uses this value
                   to identify the executable (EXE) when it is loaded in memory. The instance handle is needed for certain Windows
                   functions—for example, to load icons or bitmaps.
    hPrevInstance: has no meaning. It was used in 16-bit Windows, but is now always zero.
    pCmdLine:      contains the command-line arguments as a Unicode string.
    nCmdShow:      is a flag that says whether the main Winapplication window will be minimized, maximized, or shown normally.

    The CRT does some additional work inside main. For example, any static initializers are called before wWinMain.
    Although you can tell the linker to use a different entry-point function, use the default if you link to the CRT.
    Otherwise, the CRT initialization code will be skipped, with unpredictable results.
    (For example, global objects will not be initialized correctly.)
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    try {
        START_EASYLOGGINGPP(ac, av);

        WinApp &winapp = WinApp::getWinApp();
        Winapp.processCmdLine(ac, av);
        Winapp.runWinApp();
    } catch (Exception &e) {
        LOG(ERROR) << "Exception caught in main: " << e.getMsg() << endl;
    } catch (const std::exception &e) {
        LOG(ERROR) << "std::exception caught in main: " << e.what() << endl;
    } catch (...) {
        LOG(ERROR) << "Unknown Exception caught in main" << endl;
    }
    if (WinApp::winapp != nullptr)
        delete WinApp::winapp;
    return 0;
} /* end of main() */
