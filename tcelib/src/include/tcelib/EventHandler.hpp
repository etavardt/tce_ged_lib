#pragma once

#include <SDL2/SDL.h>

//#include "Window.hpp"
class Window;
#include <map>

class EventHandler;
typedef unsigned long long EventHandlerId;
typedef std::map<EventHandlerId, EventHandler &> RegisteredEventHandlerMap;
//typedef std::pair<unsigned long long, Window &> RegisteredWindowsPair;
typedef RegisteredEventHandlerMap::value_type RegisteredEventHandlerPair;

//TODO: create Event class and extend SDL_Event?
typedef SDL_Event Event;
typedef SDL_WindowEvent WindowEvent;
typedef SDL_AudioDeviceEvent AudioDeviceEvent;

class Window;

class EventHandler {
  private:
    static RegisteredEventHandlerMap registeredEventHandlers;

    // SDL_CommonEvent common;                 /**< Common event data */
    //void Handle(SDL_CommonEvent event);
    // SDL_DisplayEvent display;               /**< Display event data */
    // SDL_WindowEvent window;                 /**< Window event data */
    void handle(WindowEvent &event);
    // SDL_KeyboardEvent key;                  /**< Keyboard event data */
    // SDL_TextEditingEvent edit;              /**< Text editing event data */
    // SDL_TextInputEvent text;                /**< Text input event data */
    // SDL_MouseMotionEvent motion;            /**< Mouse motion event data */
    // SDL_MouseButtonEvent button;            /**< Mouse button event data */
    // SDL_MouseWheelEvent wheel;              /**< Mouse wheel event data */
    // SDL_JoyAxisEvent jaxis;                 /**< Joystick axis event data */
    // SDL_JoyBallEvent jball;                 /**< Joystick ball event data */
    // SDL_JoyHatEvent jhat;                   /**< Joystick hat event data */
    // SDL_JoyButtonEvent jbutton;             /**< Joystick button event data */
    // SDL_JoyDeviceEvent jdevice;             /**< Joystick device change event data */
    // SDL_ControllerAxisEvent caxis;          /**< Game Controller axis event data */
    // SDL_ControllerButtonEvent cbutton;      /**< Game Controller button event data */
    // SDL_ControllerDeviceEvent cdevice;      /**< Game Controller device event data */
    // SDL_ControllerTouchpadEvent ctouchpad;  /**< Game Controller touchpad event data */
    // SDL_ControllerSensorEvent csensor;      /**< Game Controller sensor event data */
    // SDL_AudioDeviceEvent adevice;           /**< Audio device event data */
    void handle(AudioDeviceEvent &event);
    // SDL_SensorEvent sensor;                 /**< Sensor event data */
    // SDL_QuitEvent quit;                     /**< Quit request event data */
    // SDL_UserEvent user;                     /**< Custom event data */
    // SDL_SysWMEvent syswm;                   /**< System dependent window event data */
    // SDL_TouchFingerEvent tfinger;           /**< Touch finger event data */
    // SDL_MultiGestureEvent mgesture;         /**< Gesture event data */
    // SDL_DollarGestureEvent dgesture;        /**< Gesture event data */
    // SDL_DropEvent drop;                     /**< Drag and drop event data */

  protected:
    // EventHandler() = default;
    // EventHandler(EventHandler const &) = delete;
    // virtual ~EventHandler() = default;
    //virtual int registerEventHandling(EventHandler &ehObject);
    virtual int registerEventHandling();
    bool pollEvent();

    void handle(Event &event);

    EventHandlerId id;

  public:
    virtual void onKeyUp(Event &event) {}
    virtual void onKeyDown(Event &event) {}

    /**< Window has been shown */
    virtual void onShown(WindowEvent &event); /**< Window has been shown */
    /**< Window has been hidden */
    virtual void onHidden(WindowEvent &event); /**< Window has been hidden */
    /**< Window has been exposed and should be redrawn */
    virtual void onExposed(WindowEvent &event); /**< Window has been exposed and should be redrawn */
    /**< Window has been moved to data1: data2 */
    virtual void onMoved(WindowEvent &event); /**< Window has been moved to data1: data2 */
    /**< Window has been resized to data1xdata2 */
    virtual void onResized(WindowEvent &event); /**< Window has been resized to data1xdata2 */
    /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
    virtual void onSizeChanged(WindowEvent &event);
    /**< Window has been minimized */
    virtual void onMinimized(WindowEvent &event);
    /**< Window has been maximized */
    virtual void onMaximized(WindowEvent &event);
    /**< Window has been restored to normal size and position */
    virtual void onRestored(WindowEvent &event);
    /**< Window has gained mouse focus */
    virtual void onEnter(WindowEvent &event);
    /**< Window has lost mouse focus */
    virtual void onLeave(WindowEvent &event);
    /**< Window has gained keyboard focus */
    virtual void onFocus(WindowEvent &event);
    /**< Window has lost keyboard focus */
    virtual void onLostFocus(WindowEvent &event);
    /**< The window manager requests that the window be closed */
    virtual void onClose(WindowEvent &event);
    /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
    virtual void onTakeFocus(WindowEvent &event);
    /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
    virtual void onHitTest(WindowEvent &event);
    /**< The ICC profile of the window's display has changed. */
    virtual void onIccProfileChanged(WindowEvent &event);
    /**< Window has been moved to display data1. */
    virtual void onDisplayChanged(WindowEvent &event);

};

// typedef union SDL_Event
// {
//     Uint32 type;                            /**< Event type, shared with all events */
//     SDL_CommonEvent common;                 /**< Common event data */
//     SDL_DisplayEvent display;               /**< Display event data */
//     SDL_WindowEvent window;                 /**< Window event data */
//     SDL_KeyboardEvent key;                  /**< Keyboard event data */
//     SDL_TextEditingEvent edit;              /**< Text editing event data */
//     SDL_TextInputEvent text;                /**< Text input event data */
//     SDL_MouseMotionEvent motion;            /**< Mouse motion event data */
//     SDL_MouseButtonEvent button;            /**< Mouse button event data */
//     SDL_MouseWheelEvent wheel;              /**< Mouse wheel event data */
//     SDL_JoyAxisEvent jaxis;                 /**< Joystick axis event data */
//     SDL_JoyBallEvent jball;                 /**< Joystick ball event data */
//     SDL_JoyHatEvent jhat;                   /**< Joystick hat event data */
//     SDL_JoyButtonEvent jbutton;             /**< Joystick button event data */
//     SDL_JoyDeviceEvent jdevice;             /**< Joystick device change event data */
//     SDL_ControllerAxisEvent caxis;          /**< Game Controller axis event data */
//     SDL_ControllerButtonEvent cbutton;      /**< Game Controller button event data */
//     SDL_ControllerDeviceEvent cdevice;      /**< Game Controller device event data */
//     SDL_ControllerTouchpadEvent ctouchpad;  /**< Game Controller touchpad event data */
//     SDL_ControllerSensorEvent csensor;      /**< Game Controller sensor event data */
//     SDL_AudioDeviceEvent adevice;           /**< Audio device event data */
//     SDL_SensorEvent sensor;                 /**< Sensor event data */
//     SDL_QuitEvent quit;                     /**< Quit request event data */
//     SDL_UserEvent user;                     /**< Custom event data */
//     SDL_SysWMEvent syswm;                   /**< System dependent window event data */
//     SDL_TouchFingerEvent tfinger;           /**< Touch finger event data */
//     SDL_MultiGestureEvent mgesture;         /**< Gesture event data */
//     SDL_DollarGestureEvent dgesture;        /**< Gesture event data */
//     SDL_DropEvent drop;                     /**< Drag and drop event data */
//
//     /* This is necessary for ABI compatibility between Visual C++ and GCC.
//        Visual C++ will respect the push pack pragma and use 52 bytes (size of
//        SDL_TextEditingEvent, the largest structure for 32-bit and 64-bit
//        architectures) for this union, and GCC will use the alignment of the
//        largest datatype within the union, which is 8 bytes on 64-bit
//        architectures.
//
//        So... we'll add padding to force the size to be 56 bytes for both.
//
//        On architectures where pointers are 16 bytes, this needs rounding up to
//        the next multiple of 16, 64, and on architectures where pointers are
//        even larger the size of SDL_UserEvent will dominate as being 3 pointers.
//     */
//     Uint8 padding[sizeof(void *) <= 8 ? 56 : sizeof(void *) == 16 ? 64 : 3 * sizeof(void *)];
// } SDL_Event;
