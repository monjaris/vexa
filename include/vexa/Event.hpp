#pragma once
#include "core/common.hpp"
#include "core/Key.hpp"
#include "time.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Event
{
public:
    enum Type : uint64;

    using Date = time::TimePoint<time::Duration<uint64, time::Millis::RATIO>>;

    class ActiveKeysState {
    public:
        bool key_data[static_cast<usize>(Key::COUNT)] = {};
        enum_t<KeyMod> mod_data = 0;

        struct Proxy {
            const ActiveKeysState& state;
            bool result;

            // Continue chain with a Key
            Proxy operator[](Key key) const noexcept {
                return Proxy{state, result && state.key_data[static_cast<usize>(key)]};
            }

            // Continue chain with a KeyMod
            Proxy operator[](KeyMod mod) const noexcept {
                return Proxy{state, result && ((state.mod_data & static_cast<uint16>(mod)) != 0)};
            }

            // Final conversion
            explicit operator bool() const noexcept {
                return result;
            }
        };

        // Entry points
        Proxy operator[](Key key) const noexcept {
            return Proxy{*this, key_data[static_cast<usize>(key)]};
        }

        Proxy operator[](KeyMod mod) const noexcept {
            return Proxy{*this, (mod_data & static_cast<uint16>(mod)) != 0};
        }
    };


private:
    struct AnyBase {
        Type type;
        uint64 date;
    };


    struct KB VX_STATIC_CLASS
    {
        struct Input : AnyBase {
            uint32 device_id;
            uint32 window_id;
            Key key;
            Keycode key_code;
            KeyMod mods;
            bool repeated;
        };

        struct Device : AnyBase {
            uint32 device_id;
        };
    };

    struct Gamepad VX_STATIC_CLASS
    {
        struct Device : AnyBase {
            uint32 device_id;
        };

        struct Axis : AnyBase {
            uint32 device_id;
            int16 value;
            uint8 axis;
        };

        struct Button : AnyBase {
            uint32 device_id;
            uint8 button;
            bool down;
        };

        struct Touchpad : AnyBase {
            uint32 device_id;
            int32 touchpad;
            int32 finger;
            float x;
            float y;
            float pressure;
        };

        struct Sensor : AnyBase {
            uint32 device_id;
        };
    };

    struct Joystick VX_STATIC_CLASS
    {
        struct Device : AnyBase {
            uint32 device_id;
        };

        struct Axis : AnyBase {
            uint32 device_id;
            int16 value;
            uint8 axis;
        };

        struct Ball : AnyBase {
            uint32 device_id;
            int16 xrel;
            int16 yrel;
            uint8 ball;
        };

        struct Hat : AnyBase {
            uint32 device_id;
            uint8 hat;
            uint8 value;
        };

        struct Button : AnyBase {
            uint32 device_id;
            uint8 button;
            bool down;
        };

        struct Battery : AnyBase {
            uint32 device_id;
            enum {UNKNOWN, ON_BATTERY, CHARGING, FULL} state;
            int percent;
        };
    };


    struct Text VX_STATIC_CLASS
    {
        struct Input : AnyBase {
            uint32 window_id;
            const char* content;
        };

        struct Editing : AnyBase {
            uint32 window_id;
            const char *text;
            int32 begin;
            int32 length;
        };

        struct EditingCandids : AnyBase {
            uint32 window_id;
            const char * const *candidates;
            int32 num_candidates;
            int32 selected_candidate;
            bool horizontal;
        };
    };


    struct Mouse VX_STATIC_CLASS
    {
        struct Device : AnyBase {
            uint32 device_id;
        };

        struct Motion : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint32 state;
            fp32 x;
            fp32 y;
            fp32 xrel;
            fp32 yrel;
        };

        struct Input : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint8 button;
            bool down;
            uint8 clicks;
            float x;
            float y;
        };

        struct Wheel : AnyBase {
            uint32 device_id;
            uint32 window_id;
            float x;
            float y;
            enum class Direction {NORMAL, FLIPPED} direction;
            float mouse_x;
            float mouse_y;
            int32 integer_x;
            int32 integer_y;
        };
    };


    struct Touch VX_STATIC_CLASS
    {
        struct Finger : AnyBase {
            uint32 window_id;
            uint64 touch_id;
            uint64 finger_id;
            float x;
            float y;
            float dx;
            float dy;
            float pressure;
        };

        struct Pinch : AnyBase {
            uint32 window_id;
            float scale;
        };

        struct Proximity : AnyBase {
            uint32 device_id;
            uint32 window_id;
        };

        struct Pen : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint32 pen_state;
            float x;
            float y;
            bool eraser;
            bool down;
        };

        struct Motion : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint32 pen_state;
            float x;
            float y;
        };

        struct Button : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint32 pen_state;
            float x;
            float y;
            uint8 button;
            bool down;
        };

        struct Axis : AnyBase {
            uint32 device_id;
            uint32 window_id;
            uint32 pen_state;
            float x;
            float y;
            enum {PRESSURE, TILT_X, TILT_Y, DIST, ROT, SLIDER, BARREL_PRESSURE} axis;
            float value;
        };
    };


    struct DisplayEvent : AnyBase { uint32 display_id; };

    struct WindowEvent : AnyBase { uint32 window_id; int32 data1; int32 data2; };

    struct AudioDeviceEvent : AnyBase { uint32 device_id; bool recording; };

    struct CameraDeviceEvent : AnyBase { uint32 device_id; };

    struct SensorEvent : AnyBase { uint32 device_id; fp32 data[6]; uint64 sensor_timestamp; };


    struct RenderEvent : AnyBase {
        uint32 window_id;
    };

    struct ExternalDropEvent : AnyBase {
        uint32 window_id;
        float x;
        float y;
        const char *source;
        const char *data;
    };

    struct ClipboardEvent : AnyBase {
        bool owner;
        int32 num_mime_types;
        const char **mime_types;
    };

    struct CustomEvent : AnyBase {
        uint32 window_id;
        int32 code;
        void *data1;
        void *data2;
    };

    struct QuitEvent : AnyBase {};


private:
    Type m_type;
    Event::Date m_date;


    union {
        KB::Input kb;
        KB::Device kb_device;

        Text::Input text;
        Text::Editing text_edit;
        Text::EditingCandids text_edit_candids;

        Mouse::Input mouse;
        Mouse::Device mouse_device;
        Mouse::Motion mouse_motion;
        Mouse::Wheel mouse_wheel;

        Joystick::Device joystick_device;
        Joystick::Axis joystick_axis;
        Joystick::Ball joystick_ball;
        Joystick::Hat joystick_hat;
        Joystick::Button joystick_button;
        Joystick::Battery joystick_battery;

        Gamepad::Device gamepad_device;
        Gamepad::Axis gamepad_axis;
        Gamepad::Button gamepad_button;
        Gamepad::Touchpad gamepad_touchpad;
        Gamepad::Sensor gamepad_sensor;

        Touch::Finger touch_finger;
        Touch::Pinch touch_pinch;
        Touch::Pen touch_pen;
        Touch::Proximity touch_proximity;
        Touch::Motion pen_motion;
        Touch::Button pen_button;
        Touch::Axis pen_axis;

        WindowEvent window;
        RenderEvent render;
        SensorEvent sensor;
        DisplayEvent display;
        ClipboardEvent clipboard;
        ExternalDropEvent extern_drop;

        AudioDeviceEvent audio_device;
        CameraDeviceEvent camera_device;

        QuitEvent quit_ev;
        CustomEvent custom_ev;
    } m;


    static void M_Fill(Event& ev, enum_t<Type> ev_type, uint64 ev_date) noexcept;

public:
    Event() noexcept;
    // rule of 5
    ~Event() noexcept;
    Event(Event&&) noexcept;
    Event(const Event&) noexcept;
    Event& operator= (const Event&) noexcept;
    Event& operator= (Event&&) noexcept;

    static ActiveKeysState ActiveKeys() noexcept;
    static std::optional<Event> Poll() noexcept;


    //  Get event type  //
    VX_NODISCARD Type type() const noexcept;
    VX_NODISCARD Date date() const noexcept;

    //  Bool-Getters  //
    VX_NODISCARD bool isFirst() const noexcept;
    VX_NODISCARD bool isLast() const noexcept;

    //  Getters  //
    VX_NODISCARD auto kb() const noexcept { return m.kb; }
    VX_NODISCARD auto kbDevice() const noexcept { return m.kb_device; };
    VX_NODISCARD auto text() const noexcept { return m.text; };
    VX_NODISCARD auto textEdit() const noexcept { return m.text_edit; };
    VX_NODISCARD auto textEditCandidates() const noexcept { return m.text_edit_candids; };
    VX_NODISCARD auto mouseButton() const noexcept { return m.mouse; };
    VX_NODISCARD auto mouseDevice() const noexcept { return m.mouse_device; };
    VX_NODISCARD auto mouseMotion() const noexcept { return m.mouse_motion; };
    VX_NODISCARD auto mouseWheel() const noexcept { return m.mouse_wheel; };
    VX_NODISCARD auto joystickDevice() const noexcept { return m.joystick_device; };
    VX_NODISCARD auto joystickAxis() const noexcept { return m.joystick_axis; };
    VX_NODISCARD auto joystickBall() const noexcept { return m.joystick_ball; };
    VX_NODISCARD auto joystickHat() const noexcept { return m.joystick_hat; };
    VX_NODISCARD auto joystickButton() const noexcept { return m.joystick_button; };
    VX_NODISCARD auto joystickBattery() const noexcept { return m.joystick_battery; };
    VX_NODISCARD auto gamepadDevice() const noexcept { return m.gamepad_device; };
    VX_NODISCARD auto gamepadAxis() const noexcept { return m.gamepad_axis; };
    VX_NODISCARD auto gamepadButton() const noexcept { return m.gamepad_button; };
    VX_NODISCARD auto gamepadTouchpad() const noexcept { return m.gamepad_touchpad; };
    VX_NODISCARD auto gamepadSensor() const noexcept { return m.gamepad_sensor; };
    VX_NODISCARD auto touchFinger() const noexcept { return m.touch_finger; };
    VX_NODISCARD auto touchPinch() const noexcept { return m.touch_pinch; };
    VX_NODISCARD auto touchPen() const noexcept { return m.touch_pen; };
    VX_NODISCARD auto touchProximity() const noexcept { return m.touch_proximity; };
    VX_NODISCARD auto pmotion() const noexcept { return m.pen_motion; };
    VX_NODISCARD auto pbutton() const noexcept { return m.pen_button; };
    VX_NODISCARD auto paxis() const noexcept { return m.pen_axis; };
    VX_NODISCARD auto windowEvent() const noexcept { return m.window; };
    VX_NODISCARD auto renderEvent() const noexcept { return m.render; };
    VX_NODISCARD auto sensorEvent() const noexcept { return m.sensor; };
    VX_NODISCARD auto displayEvent() const noexcept { return m.display; };
    VX_NODISCARD auto clipboardEvent() const noexcept { return m.clipboard; };
    VX_NODISCARD auto externalDropEvent() const noexcept { return m.extern_drop; };
    VX_NODISCARD auto audioDevice() const noexcept { return m.audio_device; };
    VX_NODISCARD auto cameraDevice() const noexcept { return m.camera_device; };
    VX_NODISCARD auto quitEvent() const noexcept { return m.quit_ev; };
    VX_NODISCARD auto customEvent() const noexcept { return m.custom_ev; };


private:
    // ..
    constexpr static inline uint64 M_ToSDL3EventTypeRuntime(Type type) noexcept;
    consteval static inline uint64 M_ToSDL3EventTypeCompt(Type type) noexcept;
    // ..
    constexpr static inline Type M_ToVexaEventTypeRuntime(uint64 type) noexcept;
    consteval static inline Type M_ToVexaEventTypeCompt(uint64 type) noexcept;
};




enum VX_NODISCARD Event::Type : uint64 {
    FIRST = 0,

    QUIT = 0x100,
    TERMINATING,
    LOW_MEMORY,
    WILL_ENTER_BACKGROUND,
    DID_ENTER_BACKGROUND,
    WILL_ENTER_FOREGROUND,
    DID_ENTER_FOREGROUND,
    LOCALE_CHANGED,
    SYSTEM_THEME_CHANGED,

    DISPLAY_ORIENTATION = 0x151,
    DISPLAY_ADDED,
    DISPLAY_REMOVED,
    DISPLAY_MOVED,
    DISPLAY_DESKTOP_MODE_CHANGED,
    DISPLAY_CURRENT_MODE_CHANGED,
    DISPLAY_CONTENT_SCALE_CHANGED,
    DISPLAY_USABLE_BOUNDS_CHANGED,
    DISPLAY_FIRST = DISPLAY_ORIENTATION,
    DISPLAY_LAST = DISPLAY_USABLE_BOUNDS_CHANGED,

    WINDOW_SHOWN = 0x202,
    WINDOW_HIDDEN,
    WINDOW_EXPOSED,
    WINDOW_MOVED,
    WINDOW_RESIZED,
    WINDOW_PIXEL_SIZE_CHANGED,
    WINDOW_METAL_VIEW_RESIZED,
    WINDOW_MINIMIZED,
    WINDOW_MAXIMIZED,
    WINDOW_RESTORED,
    WINDOW_MOUSE_ENTER,
    WINDOW_MOUSE_LEAVE,
    WINDOW_FOCUS_GAINED,
    WINDOW_FOCUS_LOST,
    WINDOW_CLOSE_REQUESTED,
    WINDOW_HIT_TEST,
    WINDOW_ICCPROF_CHANGED,
    WINDOW_DISPLAY_CHANGED,
    WINDOW_DISPLAY_SCALE_CHANGED,
    WINDOW_SAFE_AREA_CHANGED,
    WINDOW_OCCLUDED,
    WINDOW_ENTER_FULLSCREEN,
    WINDOW_LEAVE_FULLSCREEN,
    WINDOW_DESTROYED,
    WINDOW_HDR_STATE_CHANGED,
    WINDOW_FIRST = WINDOW_SHOWN,
    WINDOW_LAST = WINDOW_HDR_STATE_CHANGED,

    KEY_DOWN = 0x250,
    KEY_UP,
    TEXT_EDIT,
    TEXT_INPUT,
    KEYMAP_CHANGED,
    KEYBOARD_ADDED,
    KEYBOARD_REMOVED,
    TEXT_EDIT_CANDID,
    SCREEN_KEYBOARD_SHOWN,
    SCREEN_KEYBOARD_HIDDEN,

    MOUSE_MOTION = 0x400,
    MOUSE_BUTTON_DOWN,
    MOUSE_BUTTON_UP,
    MOUSE_WHEEL,
    MOUSE_ADDED,
    MOUSE_REMOVED,

    JOYSTICK_AXIS_MOTION = 0x600,
    JOYSTICK_BALL_MOTION,
    JOYSTICK_HAT_MOTION,
    JOYSTICK_BUTTON_DOWN,
    JOYSTICK_BUTTON_UP,
    JOYSTICK_ADDED,
    JOYSTICK_REMOVED,
    JOYSTICK_BATTERY_UPDATED,
    JOYSTICK_UPDATE_COMPLETE,

    GAMEPAD_AXIS_MOTION = 0x650,
    GAMEPAD_BUTTON_DOWN,
    GAMEPAD_BUTTON_UP,
    GAMEPAD_ADDED,
    GAMEPAD_REMOVED,
    GAMEPAD_REMAPPED,
    GAMEPAD_TOUCHPAD_DOWN,
    GAMEPAD_TOUCHPAD_MOTION,
    GAMEPAD_TOUCHPAD_UP,
    GAMEPAD_SENSOR_UPDATE,
    GAMEPAD_UPDATE_COMPLETE,
    GAMEPAD_STEAM_HANDLE_UPDATED,

    FINGER_DOWN = 0x700,
    FINGER_UP,
    FINGER_MOTION,
    FINGER_CANCELED,

    PINCH_BEGIN = 0x710,
    PINCH_UPDATE,
    PINCH_END,

    CLIPBOARD_UPDATE = 0x900,

    DROP_FILE = 0x1000,
    DROP_TEXT,
    DROP_BEGIN,
    DROP_COMPLETE,
    DROP_POSITION,

    AUDIO_DEVICE_ADDED = 0x1100,
    AUDIO_DEVICE_REMOVED,
    AUDIO_DEVICE_FORMAT_CHANGED,

    SENSOR_UPDATE = 0x1200,

    PEN_PROXIMITY_IN = 0x1300,
    PEN_PROXIMITY_OUT,
    PEN_DOWN,
    PEN_UP,
    PEN_BUTTON_DOWN,
    PEN_BUTTON_UP,
    PEN_MOTION,
    PEN_AXIS,

    CAMERA_DEVICE_ADDED = 0x1400,
    CAMERA_DEVICE_REMOVED,
    CAMERA_DEVICE_APPROVED,
    CAMERA_DEVICE_DENIED,

    RENDER_TARGETS_RESET = 0x2000,
    RENDER_DEVICE_RESET,
    RENDER_DEVICE_LOST,

    PRIVATE_0 = 0x4000,
    PRIVATE_1,
    PRIVATE_2,
    PRIVATE_3,

    POLL_SENTINEL = 0x7F00,

    CUSTOM = 0x8000,

    LAST = 0xFFFF,

    ENUM_PADDING = 0x7FFFFFFF
};



NAMESPACE_END(vexa)
