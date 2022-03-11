#pragma once

#include "Window.hpp"

class GedWindow : public Window {

  public:
    void onShown(WindowEvent &event) override;
    void onClose(WindowEvent &event) override;
};