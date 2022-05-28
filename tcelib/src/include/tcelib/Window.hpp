#pragma once

#include "EventHandler.hpp"

#include "String.hpp"
#include "Color.hpp"
#include "Image.hpp"

enum TextPosition {
    CENTERED = -1
};
class Window : public EventHandler {
private:
    // unsigned int width  = 0;
    // unsigned int height = 0;

    SDL_DisplayMode desktopDm;
    SDL_DisplayMode dm;
    SDL_DisplayMode &getDisplayMode(int displayIndex = 0);
    String getErrorMsg(String msgPrefix);

protected:
    // Color backgroundColor(0,0,0,255);
    Color backgroundColor = {0,0,0,255};
    Color foregroundColor = {255,255,255,255};

    float aspectRatio = 0.75f;
    float scale = 1.0f;

    unsigned int minWidth  = 0;
    unsigned int minHeight = 0;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    virtual void init();

    void displayText(const String &str, const int x, const int y);
    void displayImage(Image &image, const int x, const int y);

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