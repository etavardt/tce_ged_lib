#include "Image.hpp"

#include "String.hpp"
#include "Exception.hpp"

Image::Image(String &filename) {
    surface = IMG_Load(filename.c_str());
}

Image::~Image() {
    SDL_FreeSurface(surface);
}

String Image::getErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%s: Error(%s)", msgPrefix, error);
    return msg;
}
