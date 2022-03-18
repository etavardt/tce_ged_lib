#pragma once

#include "Window.hpp"

class GedWindow : public Window {
public:
    // void onShown(WindowEvent &event) override;
    void onClose(WindowEvent &event) override;
    void onKeyUp(KeyboardEvent &event) override;
    // void onExposed(WindowEvent &event) override; /**< Window has been exposed and should be redrawn */
    void onDraw(WindowEvent &event) override;
};