#pragma once

#include "EventHandler.hpp"
//#include <SDL2/SDL.h>
//#include "SdlWin.hpp"
#include "String.hpp"
//class SdlWin;


class Window : public EventHandler { //, public SdlWin {
  private:
    unsigned int width  = 0;
    unsigned int height = 0;

    SDL_DisplayMode desktopDm;
    SDL_DisplayMode dm;
    SDL_DisplayMode getDisplayMode(int displayIndex = 0);
    String getErrorMsg(String msgPrefix);

  protected:
    SDL_Window * window;
    virtual void init();

  public:
    Window();
    ~Window();

    //void createWindow(const String title, int x, int y, int w, int h, Uint32 flags);
    virtual void createWindow();
    virtual void show();

//    unsigned long long getId();
    // virtual void onShown(WindowEvent &event) override;
    // virtual void onClose(WindowEvent &event) override;
};