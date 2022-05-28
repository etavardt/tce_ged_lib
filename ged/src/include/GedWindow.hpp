#pragma once

#include "Window.hpp"

class GedWindow : public Window {
private:
    Image *image;
public:
    GedWindow();
    ~GedWindow();

    void onClose(WindowEvent &event) override;
    void onKeyUp(KeyboardEvent &event) override;
    void onDraw(WindowEvent &event) override;
    void onSizeChanged(WindowEvent &event) override;
    void onResized(WindowEvent &event) override;

    void draw();
};