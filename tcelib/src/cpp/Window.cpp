#include "Window.hpp"

#include "App.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "easylogging++.h"

Window::Window() {
}

Window::~Window() {
    LOG(TRACE) << "Window::~Window().";
    // SDL_DestroyTexture(texture);

    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    unRegisterEventHandling();
    if (window != nullptr) SDL_DestroyWindow(window);
}

void Window::createWindow() {

    LOG(TRACE) << "Pre Window.init().";
    init();

    // width  = desktopDm.w;
    // height = desktopDm.h;
    window = SDL_CreateWindow(const_cast<char *>(App::getApp().getAppFileName()),
                                          SDL_WINDOWPOS_CENTERED, //SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_CENTERED, //SDL_WINDOWPOS_UNDEFINED,
                                          desktopDm.w,
                                          desktopDm.h,
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
    //SDL_Surface *surface = SDL_GetWindowSurface(window);
    //renderer = SDL_CreateSoftwareRenderer(surface);
    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer != nullptr) {
        if (SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a) != 0) { //Set the draw color
            String msg = getErrorMsg("SDL_SetRenderDrawColor failed");
            throw Exception(msg);
        }
        if (SDL_RenderClear(renderer) != 0) { //Clear the renderer with the draw color
            String msg = getErrorMsg("SDL_RenderClear failed");
            throw Exception(msg);
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, desktopDm.w, desktopDm.h);

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

    aspectRatio = (1.0f * desktopDm.w)/desktopDm.h;
    minWidth  = desktopDm.w/2;
    minHeight = desktopDm.h/2;
}

bool Window::toggleFullscreen() {
    LOG(TRACE) << "In Window::toggleFullscreen.";
    Uint32 flags = (SDL_GetWindowFlags(window) ^ SDL_WINDOW_FULLSCREEN); // SDL_WINDOW_FULLSCREEN_DESKTOP
    if (SDL_SetWindowFullscreen(window, flags) < 0) { // NOTE: this takes FLAGS as the second param, NOT true/false!
        LOG(ERROR) << "Toggling fullscreen mode failed: " << SDL_GetError();
        return -1;
    }
    if ((flags & SDL_WINDOW_FULLSCREEN) != 0) { // SDL_WINDOW_FULLSCREEN_DESKTOP
        LOG(INFO) << "\tSDL_WINDOW_FULLSCREEN used";
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, desktopDm.w, desktopDm.h); // TODO: pass renderer as param maybe?
        return 1;
    }
    SDL_SetWindowSize(window, desktopDm.w/2, desktopDm.h/2);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    return 0;
}

void Window::displayText(const String &str, const int x, const int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(App::getApp().getFont(), str.c_str(), foregroundColor);
    if (surface == nullptr) {
        String msg = getErrorMsg("TTF_RenderText_Solid failed");
        throw Exception(msg);
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    int xPos = x;
    int yPos = y;
    if (x == CENTERED) {
        xPos = (desktopDm.w / 2) - (surface->w / 2);
    }
    if (y == CENTERED) {
        yPos = (desktopDm.h / 2) - (surface->h / 2);
    }
    SDL_Rect dstRect = {xPos, yPos, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &(surface->clip_rect), &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
};

void Window::displayImage(Image &image, const int x, const int y) {
    LOG(TRACE) << "In Window::displayImage.";
    SDL_Surface *surface = image.getSurface();
    LOG(TRACE) << "In Window::displayImage 1.";
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    LOG(TRACE) << "In Window::displayImage 2.";

    if (texture == nullptr) {
        LOG(TRACE) << "In Window::displayImage 3.";
        String msg = getErrorMsg("SDL_CreateTextureFromSurface failed");
        throw Exception(msg);
    }
    LOG(TRACE) << "In Window::displayImage 4.";

    int xPos = x;
    int yPos = y;
    if (x == CENTERED) {
        xPos = (desktopDm.w / 2) - (surface->w / 2);
    }
    if (y == CENTERED) {
        yPos = (desktopDm.h / 2) - (surface->h / 2);
    }
    SDL_Rect dstRect = {xPos, yPos, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &(surface->clip_rect), &dstRect);

    SDL_DestroyTexture(texture);
}


String Window::getErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%s: Error(%s)", msgPrefix, error);
    return msg;
}

// Event funtions

// onExposed is equivalent to windows MFC onDraw or onPaint events
void Window::onExposed(WindowEvent &event) { /**< Window has been exposed and should be redrawn */
    LOG(TRACE) << "Received the GedWindow::onExposed event.event(" << (int)event.event << ")";
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);

    //Set the draw color
    if (SDL_SetRenderDrawColor(renderer,backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a) != 0) {
        String msg = getErrorMsg("SDL_SetRenderDrawColor failed");
        throw Exception(msg);
    }
    if (SDL_RenderClear(renderer) != 0) { //Clear the renderer with the draw color
        String msg = getErrorMsg("SDL_RenderClear failed");
        throw Exception(msg);
    }

    onDraw(event);

    LOG(INFO) << "Pre SDL_RenderPresent";
    SDL_RenderPresent(renderer); //Update the renderer which will show the renderer cleared by the draw color
    //SDL_UpdateWindowSurface(window);
    LOG(INFO) << "Post SDL_RenderPresent";
}
/**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
// void Window::onSizeChanged(WindowEvent &event) {
// //    width = event.data1;
// //   height = event.data2;
// }

void Window::onDraw(WindowEvent &event) {
    LOG(INFO) << "Window::onDraw event.event(" << (int)event.event << ")";
}
