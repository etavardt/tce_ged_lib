#pragma once

#include <SDL2/SDL_image.h>
#include "String.hpp"

class Image {
private:
    String getErrorMsg(String msgPrefix);
    // SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;

public:
    Image() = default;
    Image(String &filename);
    ~Image();

    inline SDL_Surface *getSurface() { return surface; }
};