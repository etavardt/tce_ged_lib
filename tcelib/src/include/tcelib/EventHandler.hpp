#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "String.hpp"

class EventHandler;
typedef unsigned long long EventHandlerId;
typedef std::map<EventHandlerId, EventHandler &> RegisteredEventHandlerMap;
typedef RegisteredEventHandlerMap::value_type RegisteredEventHandlerPair;

//TODO: ?create Event class and extend SDL_Event?
typedef SDL_Event Event;
typedef SDL_CommonEvent CommonEvent;                          /**< Common event data */
typedef SDL_DisplayEvent DisplayEvent;                        /**< Display event data */
typedef SDL_WindowEvent WindowEvent;                          /**< Window event data */
typedef SDL_KeyboardEvent KeyboardEvent;                      /**< Keyboard event data */
typedef SDL_TextEditingEvent TextEditingEvent;                /**< Text editing event data */
typedef SDL_TextInputEvent TextInputEvent;                    /**< Text input event data */
typedef SDL_MouseMotionEvent MouseMotionEvent;                /**< Mouse motion event data */
typedef SDL_MouseButtonEvent MouseButtonEvent;                /**< Mouse button event data */ /**< ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
typedef SDL_MouseWheelEvent MouseWheelEvent;                  /**< Mouse wheel event data */
typedef SDL_JoyAxisEvent JoyAxisEvent;                        /**< Joystick axis event data */
typedef SDL_JoyBallEvent JoyBallEvent;                        /**< Joystick ball event data */
typedef SDL_JoyHatEvent JoyHatEvent;                          /**< Joystick hat event data */
typedef SDL_JoyButtonEvent JoyButtonEvent;                    /**< Joystick button event data */
typedef SDL_JoyDeviceEvent JoyDeviceEvent;                    /**< Joystick device change event data */
typedef SDL_ControllerAxisEvent ControllerAxisEvent;          /**< Game Controller axis event data */
typedef SDL_ControllerButtonEvent ControllerButtonEvent;      /**< Game Controller button event data */
typedef SDL_ControllerDeviceEvent ControllerDeviceEvent;      /**< Game Controller device event data */
typedef SDL_ControllerTouchpadEvent ControllerTouchpadEvent;  /**< Game Controller touchpad event data */
typedef SDL_ControllerSensorEvent ControllerSensorEvent;      /**< Game Controller sensor event data */
typedef SDL_AudioDeviceEvent AudioDeviceEvent;                /**< Audio device event data */
typedef SDL_SensorEvent SensorEvent;                          /**< Sensor event data */
typedef SDL_QuitEvent QuitEvent;                              /**< Quit request event data */
typedef SDL_UserEvent UserEvent;                              /**< Custom event data */
typedef SDL_SysWMEvent SysWMEvent;                            /**< System dependent window event data */
typedef SDL_TouchFingerEvent TouchFingerEvent;                /**< Touch finger event data */
typedef SDL_MultiGestureEvent MultiGestureEvent;              /**< Gesture event data */
typedef SDL_DollarGestureEvent DollarGestureEvent;            /**< Gesture event data */
typedef SDL_DropEvent DropEvent;                              /**< Drag and drop event data */

class EventHandler {
private:
    static RegisteredEventHandlerMap registeredEventHandlers;

    // SDL_CommonEvent common;                 /**< Common event data */
    // void handle(CommonEvent event); // no need to handle, call onCommon asap
    // SDL_DisplayEvent display;               /**< Display event data */
    void handle(DisplayEvent &event);
    // SDL_WindowEvent window;                 /**< Window event data */
    void handle(WindowEvent &event);
    // SDL_KeyboardEvent key;                  /**< Keyboard event data */
    void handle(KeyboardEvent &event);
    // SDL_TextEditingEvent edit;              /**< Text editing event data */
    void handle(TextEditingEvent &event);
    // SDL_TextInputEvent text;                /**< Text input event data */
    void handle(TextInputEvent &event);
    // SDL_MouseMotionEvent motion;            /**< Mouse motion event data */
    void handle(MouseMotionEvent &event);
    // SDL_MouseButtonEvent button;            /**< Mouse button event data */
    void handle(MouseButtonEvent &event);
    // SDL_MouseWheelEvent wheel;              /**< Mouse wheel event data */
    void handle(MouseWheelEvent &event);
    // SDL_JoyAxisEvent jaxis;                 /**< Joystick axis event data */
    void handle(JoyAxisEvent &event);
    // SDL_JoyBallEvent jball;                 /**< Joystick ball event data */
    void handle(JoyBallEvent &event);
    // SDL_JoyHatEvent jhat;                   /**< Joystick hat event data */
    void handle(JoyHatEvent &event);
    // SDL_JoyButtonEvent jbutton;             /**< Joystick button event data */
    void handle(JoyButtonEvent &event);
    // SDL_JoyDeviceEvent jdevice;             /**< Joystick device change event data */
    void handle(JoyDeviceEvent &event);
    // SDL_ControllerAxisEvent caxis;          /**< Game Controller axis event data */
    void handle(ControllerAxisEvent &event);
    // SDL_ControllerButtonEvent cbutton;      /**< Game Controller button event data */
    void handle(ControllerButtonEvent &event);
    // SDL_ControllerDeviceEvent cdevice;      /**< Game Controller device event data */
    void handle(ControllerDeviceEvent &event);
    // SDL_ControllerTouchpadEvent ctouchpad;  /**< Game Controller touchpad event data */
    void handle(ControllerTouchpadEvent &event);
    // SDL_ControllerSensorEvent csensor;      /**< Game Controller sensor event data */
    void handle(ControllerSensorEvent &event);
    // SDL_AudioDeviceEvent adevice;           /**< Audio device event data */
    void handle(AudioDeviceEvent &event);
    // SDL_SensorEvent sensor;                 /**< Sensor event data */
    void handle(SensorEvent &event);
    // SDL_QuitEvent quit;                     /**< Quit request event data */
    // void handle(QuitEvent &event); // no need to handle, call onQuit asap
    // SDL_UserEvent user;                     /**< Custom event data */
    void handle(UserEvent &event);
    // SDL_SysWMEvent syswm;                   /**< System dependent window event data */
    void handle(SysWMEvent &event);
    // SDL_TouchFingerEvent tfinger;           /**< Touch finger event data */
    void handle(TouchFingerEvent &event);
    // SDL_MultiGestureEvent mgesture;         /**< Gesture event data */
    void handle(MultiGestureEvent &event);
    // SDL_DollarGestureEvent dgesture;        /**< Gesture event data */
    void handle(DollarGestureEvent &event);
    // SDL_DropEvent drop;                     /**< Drag and drop event data */
    void handle(DropEvent &event);

protected:
    // EventHandler() = default;
    // EventHandler(EventHandler const &) = delete;
    // virtual ~EventHandler() = default;
    //virtual int registerEventHandling(EventHandler &ehObject);
    int registerEventHandling();
    void unRegisterEventHandling();

    // User overridable
    virtual bool pollAndHandleEvent();
    virtual void handle(Event &event);

    EventHandlerId id;

public:
    String getSdlErrorMsg(String msgPrefix);

    /**< The display orientation can't be determined */
    virtual void onDisplayOrientationUnknown(DisplayEvent &event);
    /**< The display is in landscape mode, with the right side up, relative to portrait mode */
    virtual void onDisplayOrientationLandscape(DisplayEvent &event);
    /**< The display is in landscape mode, with the left side up, relative to portrait mode */
    virtual void onDisplayOrientationLandscapeFlipped(DisplayEvent &event);
    /**< The display is in portrait mode */
    virtual void onDisplayOrientationPortrait(DisplayEvent &event);
    /**< The display is in portrait mode, upside down */
    virtual void onDisplayOrientationPortraitFlipped(DisplayEvent &event);
    /**< Display orientation has changed to data1 */
    virtual void onDisplayOrientationChanged(DisplayEvent &event);
    /**< Display has been added to the system */
    virtual void onDisplayConnected(DisplayEvent &event);
    /**< Display has been removed from the system */
    virtual void onDisplayDisconnected(DisplayEvent &event);

    virtual void onQuit(QuitEvent &event);
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

    /**< Keyboard event data */
    virtual void onKeyUp(KeyboardEvent &event);
    virtual void onKeyDown(KeyboardEvent &event);

    virtual void onKeymapChanged(Event &event);

    /**< Text editing event data */
    virtual void onTextEditing(TextEditingEvent &event);
    /**< Text input event data */
    virtual void onTextInput(TextInputEvent &event);

    /**< Mouse motion event data */
    virtual void onMouseMotion(MouseMotionEvent &event);
    /**< Mouse button event data */
    virtual void onMouseButton(MouseButtonEvent &event);
    virtual void onMouseButtonDown(MouseButtonEvent &event);
    virtual void onMouseButtonUp(MouseButtonEvent &event);
    /**< Mouse wheel event data */
    virtual void onMouseWheel(MouseWheelEvent &event);
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
