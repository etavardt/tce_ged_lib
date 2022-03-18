#include "Window.hpp"

#include "App.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "easylogging++.h"

Window::Window() {
}

Window::~Window() {
    LOG(TRACE) << "Window::~Window().";
    //SdlWin::~SdlWin();
    // SDL_DestroyTexture(texture);

    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    unRegisterEventHandling();
    if (window != nullptr) SDL_DestroyWindow(window);
}

void Window::createWindow() {

    LOG(TRACE) << "Pre Window.init().";
    init();

    width = 1024;//desktopDm.w;
    height = 768;//desktopDm.h;
    window = SDL_CreateWindow(const_cast<char *>(App::getApp().getAppFileName()),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
//                                          SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
//                                          SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
                                          SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window != nullptr) {
        id = SDL_GetWindowID(window);
        registerEventHandling();
    } else {
        String msg = getErrorMsg("SDL_Createwindow failed");
        throw Exception(msg);
    }

    // ??? onCreateClient Area ??? Renderer(?DirectX, OpenGL, SDL_Surface/SLD_Texture?) ??? User Control ???
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer != nullptr) {
        if (SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a) != 0) { //Set the draw color
            String msg = getErrorMsg("SDL_SetRenderDrawColor failed");
            throw Exception(msg);
        }
        if (SDL_RenderClear(renderer) != 0) { //Clear the renderer with the draw color
            String msg = getErrorMsg("SDL_RenderClear failed");
            throw Exception(msg);
        }
        SDL_RenderPresent(renderer); //Update the renderer which will show the renderer cleared by the draw color
    } else {
        String msg = getErrorMsg("SDL_CreateRenderer failed");
        throw Exception(msg);
    }
}

void Window::show() {
    SDL_ShowWindow(window);
}

SDL_DisplayMode &Window::getDisplayMode(int displayIndex) {
    if(SDL_GetCurrentDisplayMode(displayIndex, &dm) < 0) {
        String msg = getErrorMsg("SDL_GetCurrentDisplayMode failed");
        throw Exception(msg);
    }
    return dm;
}

void Window::init() {
    if(SDL_GetDesktopDisplayMode(0, &desktopDm)) {
        String msg = getErrorMsg("SDL_GetDesktopDisplayMode failed");
        throw Exception(msg);
    };
    getDisplayMode(0);
}

bool Window::toggleFullscreen()
{
    // LOG(TRACE) << "In Window::toggleFullscreen.";
    Uint32 flags = (SDL_GetWindowFlags(window) ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (SDL_SetWindowFullscreen(window, flags) < 0) { // NOTE: this takes FLAGS as the second param, NOT true/false!
        LOG(TRACE) << "Toggling fullscreen mode failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, width, height); // TODO: pass renderer as param maybe?
        return 1;
    }
    SDL_SetWindowSize(window, width, height);
    return 0;
}

String Window::getErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%s: Error(%s)", msgPrefix, error);
    return msg;
}

// Event funtions

// onExposed is equivalent to windows onDraw or onPaint events
void Window::onExposed(WindowEvent &event) { /**< Window has been exposed and should be redrawn */
    // LOG(TRACE) << "Received the GedWindow::onExposed event.event(" << (int)event.event << ")";
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);

    if (SDL_SetRenderDrawColor(renderer,backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a) != 0) { //Set the draw color
        String msg = getErrorMsg("SDL_SetRenderDrawColor failed");
        throw Exception(msg);
    }
    if (SDL_RenderClear(renderer) != 0) { //Clear the renderer with the draw color
        String msg = getErrorMsg("SDL_RenderClear failed");
        throw Exception(msg);
    }

    onDraw(event);

    SDL_RenderPresent(renderer); //Update the renderer which will show the renderer cleared by the draw color
}
/**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
// void Window::onSizeChanged(WindowEvent &event) {
// //    width = event.data1;
// //   height = event.data2;
// }

void Window::onDraw(WindowEvent &event) {
    LOG(INFO) << "Window::onDraw event.event(" << (int)event.event << ")";
}
