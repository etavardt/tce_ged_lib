//#include "easylogging++.h"
#include "EventHandler.hpp"

#include "Exception.hpp"
#include "Window.hpp"

#include "easylogging++.h"

#undef UNHANDLED
//#define UNHANDLED(x) LOG(DEBUG) << "Unhandled Event(" << x.type << ")";
#define UNHANDLED(x) (void)(x);

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

void EventHandler::unRegisterEventHandling() {
    registeredEventHandlers.erase(id);
}

String EventHandler::getSdlErrorMsg(String msgPrefix) {
    String error = SDL_GetError();
    String msg = format("%sError(%s)", msgPrefix, error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SdlWin Error", msg.c_str(), nullptr);

    return msg;
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

// SDL_CommonEvent common;                 /**< Common event data */
// void EventHandler::handle(CommonEvent event) {}  // no need to handle, call onCommon asap
// SDL_DisplayEvent display;               /**< Display event data */
void EventHandler::handle(DisplayEvent &event) {
    switch (event.event) { //SDL_DisplayEventID
    case SDL_DISPLAYEVENT_ORIENTATION:  /**< Display orientation has changed to data1 */
        switch (event.data1) { //SDL_DisplayOrientation
        case SDL_ORIENTATION_UNKNOWN:            /**< The display orientation can't be determined */
            onDisplayOrientationUnknown(event);
            break;
        case SDL_ORIENTATION_LANDSCAPE:          /**< The display is in landscape mode, with the right side up, relative to portrait mode */
            onDisplayOrientationLanscape(event);
            break;
        case SDL_ORIENTATION_LANDSCAPE_FLIPPED:  /**< The display is in landscape mode, with the left side up, relative to portrait mode */
            onDisplayOrientationLandscapeFlipped(event);
            break;
        case SDL_ORIENTATION_PORTRAIT:           /**< The display is in portrait mode */
            onDisplayOrientationPortrait(event);
            break;
        case SDL_ORIENTATION_PORTRAIT_FLIPPED:   /**< The display is in portrait mode, upside down */
            onDisplayOrientationPortraitFlipped(event);
            break;
        default:
            break;
        }
        onDisplayOrientationChanged(event);
        break;
    case SDL_DISPLAYEVENT_CONNECTED:    /**< Display has been added to the system */
        onDisplayConnected(event);
        break;
    case SDL_DISPLAYEVENT_DISCONNECTED: /**< Display has been removed from the system */
        onDisplayDisconnected(event);
        break;
    case SDL_DISPLAYEVENT_NONE:         /**< Never used */
    default:
        break;
    }
}
// Handle WindowEvents
//   Sends to The appropiate event handler's (Window or The App) member function for processing
//
// SDL_WindowEvent window;                 /**< Window event data */
void EventHandler::handle(WindowEvent &event) {
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
        SDL_Log("Window %d received an unknown event %d", event.windowID, event.event);
        LOG(INFO) << "Window(" << event.windowID << ") received an unknown event(" << (int)event.event << ")";
        break;
    }
    //LOG(INFO) << "WindowEvent handled: event: " << (int)event.event;
}

// Handle WindowEvents
//   Sends to The appropiate event handler's (Window or The App) member function for processing
//
// SDL_KeyboardEvent key;                  /**< Keyboard event data */
void EventHandler::handle(KeyboardEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    switch (event.type) {
      /* Keyboard events */
    case SDL_KEYDOWN:    // = 0x300, /**< Key pressed */
        eh.onKeyDown(event);
        break;
    case SDL_KEYUP:                  /**< Key released */
        eh.onKeyUp(event);
        break;
    }
    // LOG(INFO) << "KeyboardEvent handled: event: " << (int)event.type
    //           << " event.keysym.scancode: " << SDL_GetScancodeName(event.keysym.scancode)
    //           << " event.keysym.sym: " << SDL_GetKeyName(event.keysym.sym);
}
// SDL_TextInputEvent text;                /**< Text input event data */
void EventHandler::handle(TextEditingEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    eh.onTextEditing(event);
}
// SDL_TextInputEvent text;                /**< Text input event data */
void EventHandler::handle(TextInputEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    eh.onTextInput(event);
}
// SDL_MouseMotionEvent motion;            /**< Mouse motion event data */
void EventHandler::handle(MouseMotionEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    eh.onMouseMotion(event);
}
// SDL_MouseButtonEvent button;            /**< Mouse button event data */
void EventHandler::handle(MouseButtonEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:        /**< Mouse button event data */
        eh.onMouseButtonDown(event);
        break;
    case SDL_MOUSEBUTTONUP:
        eh.onMouseButtonUp(event);
        break;
    default:
        eh.onMouseButton(event);
        break;
    }
}
// SDL_MouseWheelEvent wheel;              /**< Mouse wheel event data */
void EventHandler::handle(MouseWheelEvent &event) {
    EventHandler &eh = registeredEventHandlers.at(event.windowID);
    eh.onMouseWheel(event);
}
// SDL_JoyAxisEvent jaxis;                 /**< Joystick axis event data */
void EventHandler::handle(JoyAxisEvent &event) {
    UNHANDLED(event);
}
// SDL_JoyBallEvent jball;                 /**< Joystick ball event data */
void EventHandler::handle(JoyBallEvent &event) {
    UNHANDLED(event);
}
// SDL_JoyHatEvent jhat;                   /**< Joystick hat event data */
void EventHandler::handle(JoyHatEvent &event) {
    UNHANDLED(event);
}
// SDL_JoyButtonEvent jbutton;             /**< Joystick button event data */
void EventHandler::handle(JoyButtonEvent &event) {
    UNHANDLED(event);
}
// SDL_JoyDeviceEvent jdevice;             /**< Joystick device change event data */
void EventHandler::handle(JoyDeviceEvent &event) {
    UNHANDLED(event);
}
// SDL_ControllerAxisEvent caxis;          /**< Game Controller axis event data */
void EventHandler::handle(ControllerAxisEvent &event) {
    UNHANDLED(event);
}
// SDL_ControllerButtonEvent cbutton;      /**< Game Controller button event data */
void EventHandler::handle(ControllerButtonEvent &event) {
    UNHANDLED(event);
}
// SDL_ControllerDeviceEvent cdevice;      /**< Game Controller device event data */
void EventHandler::handle(ControllerDeviceEvent &event) {
    UNHANDLED(event);
}
// SDL_ControllerTouchpadEvent ctouchpad;  /**< Game Controller touchpad event data */
void EventHandler::handle(ControllerTouchpadEvent &event) {
    UNHANDLED(event);
}
// SDL_ControllerSensorEvent csensor;      /**< Game Controller sensor event data */
void EventHandler::handle(ControllerSensorEvent &event) {
    UNHANDLED(event);
}
// SDL_AudioDeviceEvent adevice;           /**< Audio device event data */
void EventHandler::handle(SDL_AudioDeviceEvent &event) {
    UNHANDLED(event);
    // LOG(INFO) << "SDL_AudioDeviceEvent handled: which: " << event.which <<  ": iscapture: " << (int)event.iscapture;
}
// SDL_SensorEvent sensor;                 /**< Sensor event data */
void EventHandler::handle(SensorEvent &event) {
    UNHANDLED(event);
}
// SDL_QuitEvent quit;                     /**< Quit request event data */
// void EventHandler::handle(QuitEvent &event) {} // no need to handle call onQuit asap
// SDL_UserEvent user;                     /**< Custom event data */
void EventHandler::handle(UserEvent &event) {
    UNHANDLED(event);
}
// SDL_SysWMEvent syswm;                   /**< System dependent window event data */
void EventHandler::handle(SysWMEvent &event) {
    UNHANDLED(event);
}
// SDL_TouchFingerEvent tfinger;           /**< Touch finger event data */
void EventHandler::handle(TouchFingerEvent &event) {
    UNHANDLED(event);
}
// SDL_MultiGestureEvent mgesture;         /**< Gesture event data */
void EventHandler::handle(MultiGestureEvent &event) {
    UNHANDLED(event);
}
// SDL_DollarGestureEvent dgesture;        /**< Gesture event data */
void EventHandler::handle(DollarGestureEvent &event) {
    UNHANDLED(event);
}
// SDL_DropEvent drop;                     /**< Drag and drop event data */
void EventHandler::handle(DropEvent &event) {
    UNHANDLED(event);
}

void EventHandler::handle(Event &event) {
    switch (event.type) {
    /* Display events */
    case SDL_DISPLAYEVENT:
        handle(event.display);
        break;
    /* Window events */
    case SDL_WINDOWEVENT:
        handle(event.window);
        break;

    /* Keyboard events */
    case SDL_KEYDOWN:    // = 0x300, /**< Key pressed */
    case SDL_KEYUP:                  /**< Key released */
        handle(event.key);
        break;

    case SDL_TEXTEDITING:            /**< Keyboard text editing (composition) */
        handle(event.edit);
        break;
    case SDL_TEXTINPUT:              /**< Keyboard text input */
        handle(event.text);
        break;
    case SDL_KEYMAPCHANGED:          /**< Keymap changed due to a system event such as an input language or keyboard layout change. */
        onKeymapChanged(event);
        break;

    // Mouse events
    case SDL_MOUSEMOTION:
        handle(event.motion);
        break;
    case SDL_MOUSEBUTTONDOWN:        /**< Mouse button event data */
    case SDL_MOUSEBUTTONUP:
        handle(event.button);
        break;
    case SDL_MOUSEWHEEL:
        handle(event.wheel);
        break;

    case SDL_QUIT:
        onQuit(event.quit); // No Need to further use a handle event
        break;
    case SDL_AUDIODEVICEADDED: // = 0x1100, /**< A new audio device is available */
        handle(event.adevice);
        break;
    case SDL_AUDIODEVICEREMOVED: // = 0x1101, /**< An audio device has been removed. */ // Does not seem to work on my laptop
        handle(event.adevice);
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


// Display Events
/**< The display orientation can't be determined */
void EventHandler::onDisplayOrientationUnknown(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< The display is in landscape mode, with the right side up, relative to portrait mode */
void EventHandler::onDisplayOrientationLanscape(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< The display is in landscape mode, with the left side up, relative to portrait mode */
void EventHandler::onDisplayOrientationLandscapeFlipped(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< The display is in portrait mode */
void EventHandler::onDisplayOrientationPortrait(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< The display is in portrait mode, upside down */
void EventHandler::onDisplayOrientationPortraitFlipped(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< Display orientation has changed to data1 */
void EventHandler::onDisplayOrientationChanged(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< Display has been added to the system */
void EventHandler::onDisplayConnected(DisplayEvent &event) {
    UNHANDLED(event);
}
/**< Display has been removed from the system */
void EventHandler::onDisplayDisconnected(DisplayEvent &event) {
    UNHANDLED(event);
}

// Window Events
/**< Window has been shown */
void EventHandler::onShown(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been hidden */
void EventHandler::onHidden(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been exposed and should be redrawn */
void EventHandler::onExposed(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been moved to data1: data2 */
void EventHandler::onMoved(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been resized to data1xdata2 */
void EventHandler::onResized(WindowEvent &event) {
    UNHANDLED(event);
}
/**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
void EventHandler::onSizeChanged(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been minimized */
void EventHandler::onMinimized(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been maximized */
void EventHandler::onMaximized(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been restored to normal size and position */
void EventHandler::onRestored(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has gained mouse focus */
void EventHandler::onEnter(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has lost mouse focus */
void EventHandler::onLeave(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has gained keyboard focus */
void EventHandler::onFocus(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has lost keyboard focus */
void EventHandler::onLostFocus(WindowEvent &event) {
    UNHANDLED(event);
}
/**< The window manager requests that the window be closed */
void EventHandler::onClose(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
void EventHandler::onTakeFocus(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
void EventHandler::onHitTest(WindowEvent &event) {
    UNHANDLED(event);
}
/**< The ICC profile of the window's display has changed. */
void EventHandler::onIccProfileChanged(WindowEvent &event) {
    UNHANDLED(event);
}
/**< Window has been moved to display data1. */
void EventHandler::onDisplayChanged(WindowEvent &event) {
    UNHANDLED(event);
}

// Keyboard Events
/**< Key pressed */
void EventHandler::onKeyUp(KeyboardEvent &event) {
    UNHANDLED(event);
}
/**< Key released */
void EventHandler::onKeyDown(KeyboardEvent &event) {
    UNHANDLED(event);
}
/**< Keymap changed due to a system event such as an input language or keyboard layout change. */
void EventHandler::onKeymapChanged(Event &event) {
    UNHANDLED(event);
}

/**< Text editing event data */
void EventHandler::onTextEditing(TextEditingEvent &event) {
    UNHANDLED(event);
}
/**< Text input event data */
void EventHandler::onTextInput(TextInputEvent &event) {
    UNHANDLED(event);
}

// Mouse Events
/**< Mouse motion event data */
void EventHandler::onMouseMotion(MouseMotionEvent &event) {
    UNHANDLED(event);
}
/**< Mouse button event data */
void EventHandler::onMouseButton(MouseButtonEvent &event) {
    UNHANDLED(event);
}
void EventHandler::onMouseButtonDown(MouseButtonEvent &event) {
    UNHANDLED(event);
}
void EventHandler::onMouseButtonUp(MouseButtonEvent &event) {
    UNHANDLED(event);
}
/**< Mouse wheel event data */
void EventHandler::onMouseWheel(MouseWheelEvent &event) {
    UNHANDLED(event);
}

/**< Quit request event data */
void EventHandler::onQuit(QuitEvent &event) {
    UNHANDLED(event);
}

#undef UNHANDLED