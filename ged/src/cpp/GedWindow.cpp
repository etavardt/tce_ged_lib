#include "GedWindow.hpp"

#include "easylogging++.h"

#include "unused_macros.hpp"

GedWindow::GedWindow() {
    String cb = "images/Earth.jpg"; //"images/CoolBackground.jpg";
    image = new Image(cb);
}
GedWindow::~GedWindow() {
    delete image;
}

void GedWindow::onClose(WindowEvent &event) {
    UNUSED(event);
    LOG(INFO) << "Closing window";
}

void GedWindow::onKeyUp(KeyboardEvent &event) {
    LOG(TRACE) << "Received the GedWindow::onKeyUp event(" << event.type << ") scancode(" << SDL_GetScancodeName(event.keysym.scancode) << ")";
    switch (event.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE:
        break;
    case SDL_SCANCODE_F11:
        toggleFullscreen();
        break;
    case SDL_SCANCODE_F5: // Refresh the window
        draw();
        break;
    default:
        break;
    }
}

void GedWindow::onDraw(WindowEvent &event) {
    LOG(TRACE) << "Received the GedWindow::onDraw event(" << event.type << ")";
    UNUSED(event);

    draw();
}

void GedWindow::onSizeChanged(WindowEvent &event) {
    UNUSED(event);
    LOG(TRACE) << "Received the GedWindow::onSizeChanged event(" << event.type << ")";
    LOG(INFO) << "\twidth(" << event.data1 << "), height(" << event.data2 << ")";
}

void GedWindow::onResized(WindowEvent &event) {
    UNUSED(event);
    LOG(TRACE) << "Received the GedWindow::onResized event(" << event.type << ")";
    LOG(INFO) << "\twidth(" << event.data1 << "), height(" << event.data2 << ")";

    int width  = event.data1;
    int height = event.data2;
    float newAspectRatio = (float)width/(float)height;

    // Maintain aspect ratio
    if(newAspectRatio != aspectRatio) {
        if(newAspectRatio > aspectRatio) {
            height = (1.f / aspectRatio) * width;
        } else {
            width = aspectRatio * height;
        }
        if (width < minWidth || height < minHeight) {
            width = minWidth;
            height = minHeight;
        }
        //screen.w = width;
        //screen.h = height;
        LOG(INFO) << format("Setting window size to %d, %d, aspect ratio: %f\n", width, height, (float)width/(float)height);
        SDL_SetWindowSize(window, width, height); // <-- does not work
        //resizeDone = true;
    }
}

void GedWindow::draw() {
    displayImage(*image, 0,0);

    SDL_Rect rect;
    rect.h = 10;
    rect.w = 10;
    rect.x = 100;
    rect.y = 100;

    SDL_SetRenderDrawColor(renderer, foregroundColor.r, foregroundColor.g, foregroundColor.b, foregroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    displayText("Hello World!", rect.x + rect.w + 5, rect.y - 10);
    displayText("GED Test", CENTERED, 0);
    displayText("GED Test", CENTERED, CENTERED);
}
