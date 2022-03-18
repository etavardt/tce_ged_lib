#pragma once

#include <SDL2/SDL.h>

class Color : public SDL_Color {
public:
    Color() { r = 0; g = 0; b = 0; a = 255; }
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { this->r = r; this->g = g; this->b = b; this->a = a; }
    Color(const Color &c) { this->r = c.r; this->g = c.g; this->b = c.b; this->a = c.a; }
};