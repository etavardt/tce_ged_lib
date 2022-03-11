//#include "easylogging++.h"
#include "EventHandler.hpp"

#include "Exception.hpp"
#include "Window.hpp"

#include "easylogging++.h"

//typedef Exception EventException;
class EventException : public Exception {};

RegisteredEventHandlerMap EventHandler::registeredEventHandlers;

// int EventHandler::registerEventHandling(EventHandler &ehObject) {
//     registeredEventHandlers.insert(RegisteredEventHandlerPair(ehObject.id, ehObject));
//     return 1;
// }
int EventHandler::registerEventHandling() {
    registeredEventHandlers.insert(RegisteredEventHandlerPair(id, *this));
    return 1;
}
bool EventHandler::pollEvent() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        try {
            handle(event);
        } catch (EventException &e) {
            // log and ignore event
            LOG(ERROR) << e.getMsg();
        }
    }
    return (event.type != SDL_QUIT);
}

void EventHandler::handle(SDL_AudioDeviceEvent &event) {
    LOG(INFO) << "SDL_AudioDeviceEvent handled: which: " << event.which <<  ": iscapture: " << (int)event.iscapture;
}

// Handle SDL_WindowEvents
//   Sends to The appropiate event handler's (Window or The App) member function for processing
//
void EventHandler::handle(SDL_WindowEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    switch (event.event) {
      case SDL_WINDOWEVENT_NONE:           /**< Never used */
        break;
      case SDL_WINDOWEVENT_SHOWN:          /**< Window has been shown */
        eh.onShown(event);
        break;
      case SDL_WINDOWEVENT_HIDDEN:         /**< Window has been hidden */
        eh.onHidden(event);
        break;
      case SDL_WINDOWEVENT_EXPOSED:        /**< Window has been exposed and should be redrawn */
        eh.onExposed(event);
        break;
      case SDL_WINDOWEVENT_MOVED:          /**< Window has been moved to data1: data2 */
        eh.onMoved(event);
        break;
      case SDL_WINDOWEVENT_RESIZED:        /**< Window has been resized to data1xdata2 */
        eh.onResized(event);
        break;
      case SDL_WINDOWEVENT_SIZE_CHANGED:   /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
        eh.onSizeChanged(event);
        break;
      case SDL_WINDOWEVENT_MINIMIZED:      /**< Window has been minimized */
        eh.onMinimized(event);
        break;
      case SDL_WINDOWEVENT_MAXIMIZED:      /**< Window has been maximized */
        eh.onMaximized(event);
        break;
      case SDL_WINDOWEVENT_RESTORED:       /**< Window has been restored to normal size and position */
        eh.onRestored(event);
        break;
      case SDL_WINDOWEVENT_ENTER:          /**< Window has gained mouse focus */
        eh.onEnter(event);
        break;
      case SDL_WINDOWEVENT_LEAVE:          /**< Window has lost mouse focus */
        eh.onLeave(event);
        break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:   /**< Window has gained keyboard focus */
        eh.onFocus(event);
        break;
      case SDL_WINDOWEVENT_FOCUS_LOST:     /**< Window has lost keyboard focus */
        eh.onLostFocus(event);
        break;
      case SDL_WINDOWEVENT_CLOSE:          /**< The window manager requests that the window be closed */
        eh.onClose(event);
        break;
      case SDL_WINDOWEVENT_TAKE_FOCUS:     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
        eh.onTakeFocus(event);
        break;
      case SDL_WINDOWEVENT_HIT_TEST:       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
        eh.onHitTest(event);
        break;
      case SDL_WINDOWEVENT_ICCPROF_CHANGED:/**< The ICC profile of the window's display has changed. */
        eh.onIccProfileChanged(event);
        break;
      case SDL_WINDOWEVENT_DISPLAY_CHANGED:/**< Window has been moved to display data1. */
        eh.onDisplayChanged(event);
        break;
      default:
        SDL_Log("Window %d got unknown event %d", event.windowID, event.event);
        break;
    }
    LOG(INFO) << "SDL_WindowEvent handled: event: " << (int)event.event;
}

void EventHandler::handle(Event &event) {
    switch (event.type) {
      case SDL_AUDIODEVICEADDED: // = 0x1100, /**< A new audio device is available */
        handle((SDL_AudioDeviceEvent &)event);
        break;
      case SDL_AUDIODEVICEREMOVED: // = 0x1101, /**< An audio device has been removed. */ // Does not seem to work on my laptop
        handle((SDL_AudioDeviceEvent &)event);
        break;
      case SDL_WINDOWEVENT:
        handle((SDL_WindowEvent &)event);
        break;
      default:
        break;
    }
}
// /**
//  * The types of events that can be delivered.
//  */
// typedef enum
// {
//     SDL_FIRSTEVENT     = 0,     /**< Unused (do not remove) */

//     /* Application events */
//     SDL_QUIT           = 0x100, /**< User-requested quit */

//     /* These application events have special meaning on iOS, see README-ios.md for details */
//     SDL_APP_TERMINATING,        /**< The application is being terminated by the OS
//                                      Called on iOS in applicationWillTerminate()
//                                      Called on Android in onDestroy()
//                                 */
//     SDL_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
//                                      Called on iOS in applicationDidReceiveMemoryWarning()
//                                      Called on Android in onLowMemory()
//                                 */
//     SDL_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
//                                      Called on iOS in applicationWillResignActive()
//                                      Called on Android in onPause()
//                                 */
//     SDL_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
//                                      Called on iOS in applicationDidEnterBackground()
//                                      Called on Android in onPause()
//                                 */
//     SDL_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
//                                      Called on iOS in applicationWillEnterForeground()
//                                      Called on Android in onResume()
//                                 */
//     SDL_APP_DIDENTERFOREGROUND, /**< The application is now interactive
//                                      Called on iOS in applicationDidBecomeActive()
//                                      Called on Android in onResume()
//                                 */

//     SDL_LOCALECHANGED,  /**< The user's locale preferences have changed. */

//     /* Display events */
//     SDL_DISPLAYEVENT   = 0x150,  /**< Display state change */

//     /* Window events */
//     SDL_WINDOWEVENT    = 0x200, /**< Window state change */
//     SDL_SYSWMEVENT,             /**< System specific event */

//     /* Keyboard events */
//     SDL_KEYDOWN        = 0x300, /**< Key pressed */
//     SDL_KEYUP,                  /**< Key released */
//     SDL_TEXTEDITING,            /**< Keyboard text editing (composition) */
//     SDL_TEXTINPUT,              /**< Keyboard text input */
//     SDL_KEYMAPCHANGED,          /**< Keymap changed due to a system event such as an
//                                      input language or keyboard layout change.
//                                 */

//     /* Mouse events */
//     SDL_MOUSEMOTION    = 0x400, /**< Mouse moved */
//     SDL_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
//     SDL_MOUSEBUTTONUP,          /**< Mouse button released */
//     SDL_MOUSEWHEEL,             /**< Mouse wheel motion */

//     /* Joystick events */
//     SDL_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
//     SDL_JOYBALLMOTION,          /**< Joystick trackball motion */
//     SDL_JOYHATMOTION,           /**< Joystick hat position change */
//     SDL_JOYBUTTONDOWN,          /**< Joystick button pressed */
//     SDL_JOYBUTTONUP,            /**< Joystick button released */
//     SDL_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
//     SDL_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

//     /* Game controller events */
//     SDL_CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
//     SDL_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
//     SDL_CONTROLLERBUTTONUP,            /**< Game controller button released */
//     SDL_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
//     SDL_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
//     SDL_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */
//     SDL_CONTROLLERTOUCHPADDOWN,        /**< Game controller touchpad was touched */
//     SDL_CONTROLLERTOUCHPADMOTION,      /**< Game controller touchpad finger was moved */
//     SDL_CONTROLLERTOUCHPADUP,          /**< Game controller touchpad finger was lifted */
//     SDL_CONTROLLERSENSORUPDATE,        /**< Game controller sensor was updated */

//     /* Touch events */
//     SDL_FINGERDOWN      = 0x700,
//     SDL_FINGERUP,
//     SDL_FINGERMOTION,

//     /* Gesture events */
//     SDL_DOLLARGESTURE   = 0x800,
//     SDL_DOLLARRECORD,
//     SDL_MULTIGESTURE,

//     /* Clipboard events */
//     SDL_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

//     /* Drag and drop events */
//     SDL_DROPFILE        = 0x1000, /**< The system requests a file open */
//     SDL_DROPTEXT,                 /**< text/plain drag-and-drop event */
//     SDL_DROPBEGIN,                /**< A new set of drops is beginning (NULL filename) */
//     SDL_DROPCOMPLETE,             /**< Current set of drops is now complete (NULL filename) */

//     /* Audio hotplug events */
//     SDL_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
//     SDL_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

//     /* Sensor events */
//     SDL_SENSORUPDATE = 0x1200,     /**< A sensor was updated */

//     /* Render events */
//     SDL_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
//     SDL_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

//     /* Internal events */
//     SDL_POLLSENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */

//     /** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
//      *  and should be allocated with SDL_RegisterEvents()
//      */
//     SDL_USEREVENT    = 0x8000,

//     /**
//      *  This last event is only for bounding internal arrays
//      */
//     SDL_LASTEVENT    = 0xFFFF
// } SDL_EventType;

    /**< Window has been shown */
    void EventHandler::onShown(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been hidden */
    void EventHandler::onHidden(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been exposed and should be redrawn */
    void EventHandler::onExposed(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been moved to data1: data2 */
    void EventHandler::onMoved(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been resized to data1xdata2 */
    void EventHandler::onResized(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
    void EventHandler::onSizeChanged(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been minimized */
    void EventHandler::onMinimized(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been maximized */
    void EventHandler::onMaximized(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been restored to normal size and position */
    void EventHandler::onRestored(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has gained mouse focus */
    void EventHandler::onEnter(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has lost mouse focus */
    void EventHandler::onLeave(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has gained keyboard focus */
    void EventHandler::onFocus(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has lost keyboard focus */
    void EventHandler::onLostFocus(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< The window manager requests that the window be closed */
    void EventHandler::onClose(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
    void EventHandler::onTakeFocus(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
    void EventHandler::onHitTest(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< The ICC profile of the window's display has changed. */
    void EventHandler::onIccProfileChanged(WindowEvent &event) {
        // Left empty on purpose
    }
    /**< Window has been moved to display data1. */
    void EventHandler::onDisplayChanged(WindowEvent &event) {
        // Left empty on purpose
    }
