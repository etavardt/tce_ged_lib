#include "GedWindow.hpp"

#include "easylogging++.h"

void GedWindow::onShown(WindowEvent &event) {
    LOG(INFO) << "Received the GedWindow::onShown event";
}
void GedWindow::onClose(WindowEvent &event) {
    LOG(INFO) << "Received the GedWindow::onClose event";
}