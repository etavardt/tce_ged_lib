#include "GedWindow.hpp"

#include "easylogging++.h"

#include "unused_macros.hpp"

// void GedWindow::onShown(WindowEvent &event) {
//     LOG(TRACE) << "Received the GedWindow::onShown event";
//     SDL_RenderClear(renderer);
// }
void GedWindow::onClose(WindowEvent &event) {
    UNUSED(event);
    LOG(INFO) << "Closing window";
    // LOG(TRACE) << "Received the GedWindow::onClose event(" << event.type << ")";
}

void GedWindow::onKeyUp(KeyboardEvent &event) {
    // LOG(TRACE) << "Received the GedWindow::onKeyUp event(" << event.type << ")";
    switch (event.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE:
        break;
    case SDL_SCANCODE_F11:
        toggleFullscreen();
        break;
    default:
        break;
    }
}

// void GedWindow::onExposed(WindowEvent &event) { /**< Window has been exposed and should be redrawn */
//     LOG(TRACE) << "Received the GedWindow::onExposed event(" << event.type << ")";
//     SDL_RenderClear(renderer);
// }

void GedWindow::onDraw(WindowEvent &event) {
    UNUSED(event);

    SDL_Rect rect;
    rect.h = 10;
    rect.w = 10;
    rect.x = 0;
    rect.y = 0;

    SDL_SetRenderDrawColor(renderer, foregroundColor.r, foregroundColor.g, foregroundColor.b, foregroundColor.a);
    SDL_RenderDrawRect(renderer, &rect);
}
