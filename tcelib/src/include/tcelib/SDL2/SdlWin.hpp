#pragma once

#include <SDL2/SDL.h>

#include "String.hpp"

class SdlWin {
  public:
    SdlWin();
    virtual ~SdlWin() = default;

    //void createWindow(const String title, int x, int y, int w, int h, Uint32 flags);
    void createWindow();
    void init();
    void show();

    SDL_Event pullEvent();

  private:
    unsigned int width  = 0;
    unsigned int height = 0;

    SDL_Window *window = nullptr;

    SDL_DisplayMode desktopDm;
    SDL_DisplayMode dm;
    void getDisplayMode(int displayIndex = 0);
    String getErrorMsg(String msgPrefix);

};