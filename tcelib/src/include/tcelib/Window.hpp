#pragma once

#include "EventHandler.hpp"

#include "String.hpp"
#include "Color.hpp"

class Window : public EventHandler {
private:
    unsigned int width  = 0;
    unsigned int height = 0;

    SDL_DisplayMode desktopDm;
    SDL_DisplayMode dm;
    SDL_DisplayMode &getDisplayMode(int displayIndex = 0);
    String getErrorMsg(String msgPrefix);

protected:
    //Color backgroundColor(0,0,0,255);
    Color backgroundColor = {0,0,0,255};
    Color foregroundColor = {255,255,255,255};

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    virtual void init();

public:
    Window();
    ~Window();

    bool toggleFullscreen();

    //void createWindow(const String title, int x, int y, int w, int h, Uint32 flags);
    virtual void createWindow();
    virtual void show();

    // Event functions
    void onExposed(WindowEvent &event) override; /**< Window has been exposed and should be redrawn */
    /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
    // void onSizeChanged(WindowEvent &event) override;

    // Window Specific
    virtual void onDraw(WindowEvent &event);
};