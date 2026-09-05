#include <utility>
#include "vexa/alt/SDL3.h"
#include "vexa/Event.hpp"


// store global event object without PIMPL
namespace internal {
    SDL_Event event;
};


NAMESPACE_BEGIN(vexa)

using This = Event;


struct TypeMap {
    This::Type type;
    uint64 sdl_type;
};


static constexpr TypeMap type_maps[] = {
    { This::FIRST, SDL_EVENT_FIRST },

    { This::QUIT, SDL_EVENT_QUIT },
    { This::TERMINATING, SDL_EVENT_TERMINATING },
    { This::LOW_MEMORY, SDL_EVENT_LOW_MEMORY },
    { This::WILL_ENTER_BACKGROUND, SDL_EVENT_WILL_ENTER_BACKGROUND },
    { This::DID_ENTER_BACKGROUND, SDL_EVENT_DID_ENTER_BACKGROUND },
    { This::WILL_ENTER_FOREGROUND, SDL_EVENT_WILL_ENTER_FOREGROUND },
    { This::DID_ENTER_FOREGROUND, SDL_EVENT_DID_ENTER_FOREGROUND },
    { This::LOCALE_CHANGED, SDL_EVENT_LOCALE_CHANGED },
    { This::SYSTEM_THEME_CHANGED, SDL_EVENT_SYSTEM_THEME_CHANGED },

    { This::DISPLAY_ORIENTATION, SDL_EVENT_DISPLAY_ORIENTATION },
    { This::DISPLAY_ADDED, SDL_EVENT_DISPLAY_ADDED },
    { This::DISPLAY_REMOVED, SDL_EVENT_DISPLAY_REMOVED },
    { This::DISPLAY_MOVED, SDL_EVENT_DISPLAY_MOVED },
    { This::DISPLAY_DESKTOP_MODE_CHANGED, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED },
    { This::DISPLAY_CURRENT_MODE_CHANGED, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED },
    { This::DISPLAY_CONTENT_SCALE_CHANGED, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED },
    { This::DISPLAY_USABLE_BOUNDS_CHANGED, SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED },
    { This::DISPLAY_FIRST, SDL_EVENT_DISPLAY_FIRST },
    { This::DISPLAY_LAST, SDL_EVENT_DISPLAY_LAST },

    { This::WINDOW_SHOWN, SDL_EVENT_WINDOW_SHOWN },
    { This::WINDOW_HIDDEN, SDL_EVENT_WINDOW_HIDDEN },
    { This::WINDOW_EXPOSED, SDL_EVENT_WINDOW_EXPOSED },
    { This::WINDOW_MOVED, SDL_EVENT_WINDOW_MOVED },
    { This::WINDOW_RESIZED, SDL_EVENT_WINDOW_RESIZED },
    { This::WINDOW_PIXEL_SIZE_CHANGED, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED },
    { This::WINDOW_METAL_VIEW_RESIZED, SDL_EVENT_WINDOW_METAL_VIEW_RESIZED },
    { This::WINDOW_MINIMIZED, SDL_EVENT_WINDOW_MINIMIZED },
    { This::WINDOW_MAXIMIZED, SDL_EVENT_WINDOW_MAXIMIZED },
    { This::WINDOW_RESTORED, SDL_EVENT_WINDOW_RESTORED },
    { This::WINDOW_MOUSE_ENTER, SDL_EVENT_WINDOW_MOUSE_ENTER },
    { This::WINDOW_MOUSE_LEAVE, SDL_EVENT_WINDOW_MOUSE_LEAVE },
    { This::WINDOW_FOCUS_GAINED, SDL_EVENT_WINDOW_FOCUS_GAINED },
    { This::WINDOW_FOCUS_LOST, SDL_EVENT_WINDOW_FOCUS_LOST },
    { This::WINDOW_CLOSE_REQUESTED, SDL_EVENT_WINDOW_CLOSE_REQUESTED },
    { This::WINDOW_HIT_TEST, SDL_EVENT_WINDOW_HIT_TEST },
    { This::WINDOW_ICCPROF_CHANGED, SDL_EVENT_WINDOW_ICCPROF_CHANGED },
    { This::WINDOW_DISPLAY_CHANGED, SDL_EVENT_WINDOW_DISPLAY_CHANGED },
    { This::WINDOW_DISPLAY_SCALE_CHANGED, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED },
    { This::WINDOW_SAFE_AREA_CHANGED, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED },
    { This::WINDOW_OCCLUDED, SDL_EVENT_WINDOW_OCCLUDED },
    { This::WINDOW_ENTER_FULLSCREEN, SDL_EVENT_WINDOW_ENTER_FULLSCREEN },
    { This::WINDOW_LEAVE_FULLSCREEN, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN },
    { This::WINDOW_DESTROYED, SDL_EVENT_WINDOW_DESTROYED },
    { This::WINDOW_HDR_STATE_CHANGED, SDL_EVENT_WINDOW_HDR_STATE_CHANGED },
    { This::WINDOW_FIRST, SDL_EVENT_WINDOW_FIRST },
    { This::WINDOW_LAST, SDL_EVENT_WINDOW_LAST },

    { This::KEY_DOWN, SDL_EVENT_KEY_DOWN },
    { This::KEY_UP, SDL_EVENT_KEY_UP },
    { This::TEXT_EDIT, SDL_EVENT_TEXT_EDITING },
    { This::TEXT_INPUT, SDL_EVENT_TEXT_INPUT },
    { This::KEYMAP_CHANGED, SDL_EVENT_KEYMAP_CHANGED },
    { This::KEYBOARD_ADDED, SDL_EVENT_KEYBOARD_ADDED },
    { This::KEYBOARD_REMOVED, SDL_EVENT_KEYBOARD_REMOVED },
    { This::TEXT_EDIT_CANDID, SDL_EVENT_TEXT_EDITING_CANDIDATES },
    { This::SCREEN_KEYBOARD_SHOWN, SDL_EVENT_SCREEN_KEYBOARD_SHOWN },
    { This::SCREEN_KEYBOARD_HIDDEN, SDL_EVENT_SCREEN_KEYBOARD_HIDDEN },

    { This::MOUSE_MOTION, SDL_EVENT_MOUSE_MOTION },
    { This::MOUSE_BUTTON_DOWN, SDL_EVENT_MOUSE_BUTTON_DOWN },
    { This::MOUSE_BUTTON_UP, SDL_EVENT_MOUSE_BUTTON_UP },
    { This::MOUSE_WHEEL, SDL_EVENT_MOUSE_WHEEL },
    { This::MOUSE_ADDED, SDL_EVENT_MOUSE_ADDED },
    { This::MOUSE_REMOVED, SDL_EVENT_MOUSE_REMOVED },

    { This::JOYSTICK_AXIS_MOTION, SDL_EVENT_JOYSTICK_AXIS_MOTION },
    { This::JOYSTICK_BALL_MOTION, SDL_EVENT_JOYSTICK_BALL_MOTION },
    { This::JOYSTICK_HAT_MOTION, SDL_EVENT_JOYSTICK_HAT_MOTION },
    { This::JOYSTICK_BUTTON_DOWN, SDL_EVENT_JOYSTICK_BUTTON_DOWN },
    { This::JOYSTICK_BUTTON_UP, SDL_EVENT_JOYSTICK_BUTTON_UP },
    { This::JOYSTICK_ADDED, SDL_EVENT_JOYSTICK_ADDED },
    { This::JOYSTICK_REMOVED, SDL_EVENT_JOYSTICK_REMOVED },
    { This::JOYSTICK_BATTERY_UPDATED, SDL_EVENT_JOYSTICK_BATTERY_UPDATED },
    { This::JOYSTICK_UPDATE_COMPLETE, SDL_EVENT_JOYSTICK_UPDATE_COMPLETE },

    { This::GAMEPAD_AXIS_MOTION, SDL_EVENT_GAMEPAD_AXIS_MOTION },
    { This::GAMEPAD_BUTTON_DOWN, SDL_EVENT_GAMEPAD_BUTTON_DOWN },
    { This::GAMEPAD_BUTTON_UP, SDL_EVENT_GAMEPAD_BUTTON_UP },
    { This::GAMEPAD_ADDED, SDL_EVENT_GAMEPAD_ADDED },
    { This::GAMEPAD_REMOVED, SDL_EVENT_GAMEPAD_REMOVED },
    { This::GAMEPAD_REMAPPED, SDL_EVENT_GAMEPAD_REMAPPED },
    { This::GAMEPAD_TOUCHPAD_DOWN, SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN },
    { This::GAMEPAD_TOUCHPAD_MOTION, SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION },
    { This::GAMEPAD_TOUCHPAD_UP, SDL_EVENT_GAMEPAD_TOUCHPAD_UP },
    { This::GAMEPAD_SENSOR_UPDATE, SDL_EVENT_GAMEPAD_SENSOR_UPDATE },
    { This::GAMEPAD_UPDATE_COMPLETE, SDL_EVENT_GAMEPAD_UPDATE_COMPLETE },
    { This::GAMEPAD_STEAM_HANDLE_UPDATED, SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED },

    { This::FINGER_DOWN, SDL_EVENT_FINGER_DOWN },
    { This::FINGER_UP, SDL_EVENT_FINGER_UP },
    { This::FINGER_MOTION, SDL_EVENT_FINGER_MOTION },
    { This::FINGER_CANCELED, SDL_EVENT_FINGER_CANCELED },

    { This::PINCH_BEGIN, SDL_EVENT_PINCH_BEGIN },
    { This::PINCH_UPDATE, SDL_EVENT_PINCH_UPDATE },
    { This::PINCH_END, SDL_EVENT_PINCH_END },

    { This::CLIPBOARD_UPDATE, SDL_EVENT_CLIPBOARD_UPDATE },

    { This::DROP_FILE, SDL_EVENT_DROP_FILE },
    { This::DROP_TEXT, SDL_EVENT_DROP_TEXT },
    { This::DROP_BEGIN, SDL_EVENT_DROP_BEGIN },
    { This::DROP_COMPLETE, SDL_EVENT_DROP_COMPLETE },
    { This::DROP_POSITION, SDL_EVENT_DROP_POSITION },

    { This::AUDIO_DEVICE_ADDED, SDL_EVENT_AUDIO_DEVICE_ADDED },
    { This::AUDIO_DEVICE_REMOVED, SDL_EVENT_AUDIO_DEVICE_REMOVED },
    { This::AUDIO_DEVICE_FORMAT_CHANGED, SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED },

    { This::SENSOR_UPDATE, SDL_EVENT_SENSOR_UPDATE },

    { This::PEN_PROXIMITY_IN, SDL_EVENT_PEN_PROXIMITY_IN },
    { This::PEN_PROXIMITY_OUT, SDL_EVENT_PEN_PROXIMITY_OUT },
    { This::PEN_DOWN, SDL_EVENT_PEN_DOWN },
    { This::PEN_UP, SDL_EVENT_PEN_UP },
    { This::PEN_BUTTON_DOWN, SDL_EVENT_PEN_BUTTON_DOWN },
    { This::PEN_BUTTON_UP, SDL_EVENT_PEN_BUTTON_UP },
    { This::PEN_MOTION, SDL_EVENT_PEN_MOTION },
    { This::PEN_AXIS, SDL_EVENT_PEN_AXIS },

    { This::CAMERA_DEVICE_ADDED, SDL_EVENT_CAMERA_DEVICE_ADDED },
    { This::CAMERA_DEVICE_REMOVED, SDL_EVENT_CAMERA_DEVICE_REMOVED },
    { This::CAMERA_DEVICE_APPROVED, SDL_EVENT_CAMERA_DEVICE_APPROVED },
    { This::CAMERA_DEVICE_DENIED, SDL_EVENT_CAMERA_DEVICE_DENIED },

    { This::RENDER_TARGETS_RESET, SDL_EVENT_RENDER_TARGETS_RESET },
    { This::RENDER_DEVICE_RESET, SDL_EVENT_RENDER_DEVICE_RESET },
    { This::RENDER_DEVICE_LOST, SDL_EVENT_RENDER_DEVICE_LOST },

    { This::PRIVATE_0, SDL_EVENT_PRIVATE0 },
    { This::PRIVATE_1, SDL_EVENT_PRIVATE1 },
    { This::PRIVATE_2, SDL_EVENT_PRIVATE2 },
    { This::PRIVATE_3, SDL_EVENT_PRIVATE3 },

    { This::POLL_SENTINEL, SDL_EVENT_POLL_SENTINEL },

    { This::CUSTOM, SDL_EVENT_USER },

    { This::LAST, SDL_EVENT_LAST },
};


constexpr inline uint64 This::M_ToSDL3EventTypeRuntime(This::Type type) noexcept
{
    for(const auto& [mk_type, sdl_type] : type_maps)  if(mk_type == type)  return sdl_type;
    std::unreachable();
}
consteval inline uint64 This::M_ToSDL3EventTypeCompt(This::Type type) noexcept
{
    return M_ToSDL3EventTypeRuntime(type);
}

constexpr inline This::Type This::M_ToVexaEventTypeRuntime(uint64 sdl_type) noexcept
{
    for(const auto& [mk_type, _sdl_type] : type_maps)  if(_sdl_type == sdl_type)  return mk_type;
    std::unreachable();
}
consteval inline This::Type This::M_ToVexaEventTypeCompt(uint64 type) noexcept
{
    return M_ToVexaEventTypeRuntime(type);
}



This::Event() noexcept {
    m.kb.date = m.kb_device.date =
    m.text.date = m.text_edit.date = m.text_edit_candids.date =
    m.mouse.date = m.mouse_device.date = m.mouse_motion.date = m.mouse_wheel.date =
    m.joystick_device.date = m.joystick_axis.date = m.joystick_ball.date =
    m.joystick_ball.date = m.joystick_button.date = m.joystick_battery.date =
    m.gamepad_device.date = m.gamepad_axis.date = m.gamepad_button.date =
    m.gamepad_touchpad.date = m.gamepad_sensor.date =
    m.touch_finger.date = m.touch_pinch.date = m.touch_pen.date = m.touch_proximity.date =
    m.pen_motion.date = m.pen_button.date = m.pen_axis.date =
    m.window.date = m.renderer.date = m.sensor.date = m.display.date =
    m.clipboard.date = m.extern_drop.date = m.audio_device.date = m.camera_device.date =
    m.quit_ev.date = m.custom_ev.date
        =
            m_date.sinceEpoch().millis();

    m.kb.type = m.kb_device.type =
    m.text.type = m.text_edit.type = m.text_edit_candids.type =
    m.mouse.type = m.mouse_device.type = m.mouse_motion.type = m.mouse_wheel.type =
    m.joystick_device.type = m.joystick_axis.type = m.joystick_ball.type =
    m.joystick_ball.type = m.joystick_button.type = m.joystick_battery.type =
    m.gamepad_device.type = m.gamepad_axis.type = m.gamepad_button.type =
    m.gamepad_touchpad.type = m.gamepad_sensor.type =
    m.touch_finger.type = m.touch_pinch.type = m.touch_pen.type = m.touch_proximity.type =
    m.pen_motion.type = m.pen_button.type = m.pen_axis.type =
    m.window.type = m.renderer.type = m.sensor.type = m.display.type =
    m.clipboard.type = m.extern_drop.type = m.audio_device.type = m.camera_device.type =
    m.quit_ev.type = m.custom_ev.type
        =
            m_type;
}


// set all default
This::~Event() noexcept = default;
This::Event(Event&&) noexcept = default;
This::Event(const Event&) noexcept = default;
Event& This::operator= (const Event&) noexcept = default;
Event& This::operator= (Event&&) noexcept = default;




This::ActiveKeysState This::ActiveKeys() noexcept {
    ActiveKeysState aks;

    // copy sdl keyboard state to internal buffer
    std::copy_n(SDL_GetKeyboardState(nullptr), enum_v(Key::COUNT), aks.keyData());

    // copy sdl key modifier state to internal variable
    aks.modData() = SDL_GetModState();

    return aks;
}



void This::M_Fill(Event& ev, enum_t<Type> ev_type, uint64 ev_date) noexcept {
    namespace i = internal;

    switch (ev.m_type)
    {
        //  KEYBOARD  //
        CASE_OR (KEY_DOWN, KEY_UP): {
            ev.m.kb = KB::Input {
                {Type{ev_type}, ev_date},
                i::event.key.which,
                i::event.key.windowID,
                CAST<Key>(i::event.key.scancode),
                CAST<Keycode>(i::event.key.key),
                CAST<KeyMod>(i::event.key.mod),
                i::event.key.repeat
            };

            break;
        }
        CASE_OR(KEYBOARD_ADDED, KEYBOARD_REMOVED): {
            ev.m.kb_device = KB::Device {
                {Type{ev_type}, ev_date},
                i::event.kdevice.which
            };
            break;
        }

        //  TEXT INPUT  //
        case Type::TEXT_INPUT: {
            ev.m.text = Text::Input {
                {Type{ev_type}, ev_date},
                i::event.text.windowID,
                i::event.text.text
            };
            break;
        }
        case Type::TEXT_EDIT: {
            ev.m.text_edit = Text::Editing {
                {Type{ev_type}, ev_date},
                i::event.edit.windowID,
                i::event.edit.text,
                i::event.edit.start,
                i::event.edit.length
            };
            break;
        }
        case Type::TEXT_EDIT_CANDID: {
            ev.m.text_edit_candids = Text::EditingCandids {
                {Type{ev_type}, ev_date},
                i::event.edit_candidates.windowID,
                i::event.edit_candidates.candidates,
                i::event.edit_candidates.num_candidates,
                i::event.edit_candidates.selected_candidate,
                static_cast<bool>(i::event.edit_candidates.horizontal)
            };
            break;
        }

        //  MOUSE  //
        case Type::MOUSE_MOTION: {
            ev.m.mouse_motion = Mouse::Motion {
                {Type{ev_type}, ev_date},
                i::event.motion.which,
                i::event.motion.windowID,
                i::event.motion.state,
                i::event.motion.x,
                i::event.motion.y,
                i::event.motion.xrel,
                i::event.motion.yrel
            };
            break;
        }
        CASE_OR(MOUSE_BUTTON_DOWN, MOUSE_BUTTON_UP): {
            ev.m.mouse = Mouse::Input {
                {Type{ev_type}, ev_date},
                i::event.button.which,
                i::event.button.windowID,
                i::event.button.button,
                i::event.button.down,
                i::event.button.clicks,
                i::event.button.x,
                i::event.button.y
            };
            break;
        }
        case Type::MOUSE_WHEEL: {
            ev.m.mouse_wheel = Mouse::Wheel {
                {Type{ev_type}, ev_date},
                i::event.wheel.which,
                i::event.wheel.windowID,
                i::event.wheel.x,
                i::event.wheel.y,
                (i::event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                    ? Mouse::Wheel::Direction::FLIPPED
                    : Mouse::Wheel::Direction::NORMAL,
                i::event.wheel.mouse_x,
                i::event.wheel.mouse_y,
                // AMBIGUOUS: Integer scroll offsets (integer_x/y) do not exist directly on SDL_MouseWheelEvent in SDL3.
                // SDL3 wheel deltas are native floats (event.wheel.x / y).
                0,
                0
            };
            break;
        }
        CASE_OR(MOUSE_ADDED, MOUSE_REMOVED): {
            ev.m.mouse_device = Mouse::Device {
                {Type{ev_type}, ev_date},
                i::event.mdevice.which
            };
            break;
        }

        //  JOYSTICK  //
        case Type::JOYSTICK_AXIS_MOTION: {
            ev.m.joystick_axis = Joystick::Axis {
                {Type{ev_type}, ev_date},
                i::event.jaxis.which,
                i::event.jaxis.value,
                i::event.jaxis.axis
            };
            break;
        }
        case Type::JOYSTICK_BALL_MOTION: {
            ev.m.joystick_ball = Joystick::Ball {
                {Type{ev_type}, ev_date},
                i::event.jball.which,
                i::event.jball.xrel,
                i::event.jball.yrel,
                i::event.jball.ball
            };
            break;
        }
        case Type::JOYSTICK_HAT_MOTION: {
            ev.m.joystick_hat = Joystick::Hat {
                {Type{ev_type}, ev_date},
                i::event.jhat.which,
                i::event.jhat.hat,
                i::event.jhat.value
            };
            break;
        }
        CASE_OR(JOYSTICK_BUTTON_DOWN, JOYSTICK_BUTTON_UP): {
            ev.m.joystick_button = Joystick::Button {
    {Type{ev_type}, ev_date},
                i::event.jbutton.which,
                i::event.jbutton.button,
                i::event.jbutton.down
            };
            break;
        }
        case Type::JOYSTICK_BATTERY_UPDATED: {
            ev.m.joystick_battery = Joystick::Battery {
    {Type{ev_type}, ev_date},
                i::event.jbattery.which,
                Joystick::Battery::UNKNOWN,
                i::event.jbattery.percent
            };
            break;
        }
        CASE_OR(JOYSTICK_ADDED, JOYSTICK_REMOVED): {
            ev.m.joystick_device = Joystick::Device {
    {Type{ev_type}, ev_date},
                i::event.jdevice.which
            };
            break;
        }

        //  GAMEPAD  //
        case Type::GAMEPAD_AXIS_MOTION: {
            ev.m.gamepad_axis = Gamepad::Axis {
    {Type{ev_type}, ev_date},
                i::event.gaxis.which,
                i::event.gaxis.value,
                i::event.gaxis.axis
            };
            break;
        }
        CASE_OR(GAMEPAD_BUTTON_DOWN, GAMEPAD_BUTTON_UP): {
            ev.m.gamepad_button = Gamepad::Button {
    {Type{ev_type}, ev_date},
                i::event.gbutton.which,
                i::event.gbutton.button,
                i::event.gbutton.down
            };
            break;
        }
        CASE_OR(GAMEPAD_ADDED, GAMEPAD_REMOVED): {
            ev.m.gamepad_device = Gamepad::Device {
    {Type{ev_type}, ev_date},
                i::event.gdevice.which
            };
            break;
        }
        case Type::GAMEPAD_TOUCHPAD_DOWN:
        case Type::GAMEPAD_TOUCHPAD_MOTION:
        case Type::GAMEPAD_TOUCHPAD_UP: {
            ev.m.gamepad_touchpad = Gamepad::Touchpad {
    {Type{ev_type}, ev_date},
                i::event.gtouchpad.which,
                i::event.gtouchpad.touchpad,
                i::event.gtouchpad.finger,
                i::event.gtouchpad.x,
                i::event.gtouchpad.y,
                i::event.gtouchpad.pressure
            };
            break;
        }
        case Type::GAMEPAD_SENSOR_UPDATE: {
            ev.m.gamepad_sensor = Gamepad::Sensor {
    {Type{ev_type}, ev_date},
                i::event.gsensor.which
            };
            break;
        }

        //  TOUCH  //
        case Type::FINGER_DOWN:
        case Type::FINGER_UP:
        case Type::FINGER_MOTION:
        case Type::FINGER_CANCELED: {
            ev.m.touch_finger = Touch::Finger {
    {Type{ev_type}, ev_date},
                i::event.tfinger.windowID,
                i::event.tfinger.touchID,
                i::event.tfinger.fingerID,
                i::event.tfinger.x,
                i::event.tfinger.y,
                i::event.tfinger.dx,
                i::event.tfinger.dy,
                i::event.tfinger.pressure
            };
            break;
        }
        case Type::PEN_PROXIMITY_IN:
        case Type::PEN_PROXIMITY_OUT: {
            ev.m.touch_proximity = Touch::Proximity {
                {Type{ev_type}, ev_date},
                i::event.pproximity.which,
                i::event.pproximity.windowID
            };
            break;
        }
        case Type::PEN_MOTION: {
            ev.m.pen_motion = Touch::Motion {
                {Type{ev_type}, ev_date},
                i::event.pmotion.which,
                i::event.pmotion.windowID,
                i::event.pmotion.pen_state,
                i::event.pmotion.x,
                i::event.pmotion.y
            };
            break;
        }
        CASE_OR(PEN_BUTTON_DOWN, PEN_BUTTON_UP): {
            ev.m.pen_button = Touch::Button {
                {Type{ev_type}, ev_date},
                i::event.pbutton.which,
                i::event.pbutton.windowID,
                i::event.pbutton.pen_state,
                i::event.pbutton.x,
                i::event.pbutton.y,
                i::event.pbutton.button,
                i::event.pbutton.down
            };
            break;
        }
        case Type::PEN_AXIS: {
            // AMBIGUOUS: SDL_PenAxisEvent maps axis values using SDL_PenAxis enum values.
            // Converting directly to internal Touch::Axis::axis representation.
            ev.m.pen_axis = Touch::Axis {
                {Type{ev_type}, ev_date},
                i::event.paxis.which,
                i::event.paxis.windowID,
                i::event.paxis.pen_state,
                i::event.paxis.x,
                i::event.paxis.y,
                static_cast<decltype(Touch::Axis::axis)>(i::event.paxis.axis),
                i::event.paxis.value
            };
            break;
        }

        //  DROP  //
        case Type::DROP_FILE:
        case Type::DROP_TEXT:
        case Type::DROP_BEGIN:
        case Type::DROP_COMPLETE:
        case Type::DROP_POSITION: {
            ev.m.extern_drop = ExternalDropEvent {
                {Type{ev_type}, ev_date},
                i::event.drop.windowID,
                i::event.drop.x,
                i::event.drop.y,
                i::event.drop.source,
                i::event.drop.data
            };
            break;
        }

        //  WINDOW EVENTS  //
        case Type::WINDOW_SHOWN ... Type::WINDOW_HDR_STATE_CHANGED: {
            ev.m.window = WindowEvent {
                {Type{ev_type}, ev_date},
                i::event.window.windowID,
                i::event.window.data1,
                i::event.window.data2
            };
            break;
        }

        //  DISPLAY EVENTS  //
        case Type::DISPLAY_ORIENTATION ... Type::DISPLAY_USABLE_BOUNDS_CHANGED: {
            ev.m.display = DisplayEvent {
                {Type{ev_type}, ev_date},
                i::event.display.displayID
            };
            break;
        }

        //  SENSOR EVENTS  //
        case Type::SENSOR_UPDATE: {
            ev.m.sensor = SensorEvent {
                {Type{ev_type}, ev_date},
                i::event.sensor.which,
                {
                    i::event.sensor.data[0], i::event.sensor.data[1], i::event.sensor.data[2],
                    i::event.sensor.data[3], i::event.sensor.data[4], i::event.sensor.data[5]
                },
                i::event.sensor.sensor_timestamp
            };
            break;
        }

        //  CLIPBOARD EVENTS  //
        case Type::CLIPBOARD_UPDATE: {
            ev.m.clipboard = ClipboardEvent {
                {Type{ev_type}, ev_date},
                i::event.clipboard.owner,
                i::event.clipboard.num_mime_types,
                i::event.clipboard.mime_types
            };
            break;
        }

        //  SPECIAL EVENTS  //
        case Type::QUIT: {
            ev.m.quit_ev = QuitEvent {
                {Type{ev_type}, ev_date}
            };
            break;
        }

        case Type::CUSTOM: {
            ev.m.custom_ev = CustomEvent {
                {Type{ev_type}, ev_date},
                i::event.user.windowID, i::event.user.code,
                i::event.user.data1, i::event.user.data2
            };
            break;
        }

        default : { break; }
    }
}


void This::m_toVexaEvent(SDL_Event* sdl_event) noexcept {
    m_type = M_ToVexaEventTypeRuntime(sdl_event->type);
    m_date = Event::Date::DurationT{sdl_event->common.timestamp};
}


std::optional<Event> Event::Poll() noexcept {
    namespace i = internal;

    if (!SDL_PollEvent(&i::event)) return std::nullopt;

    Event build;
    build.m_toVexaEvent(&i::event);
    M_Fill(build, build.m_type, build.m_date.sinceEpoch().millis());

    return build;
}



This::Type This::type() const noexcept {
    return m_type;
}

VX_NODISCARD This::Date This::date() const noexcept {
    return m_date;
}

bool This::isFirst() const noexcept {
    return m_type == Type::FIRST;
}

bool This::isLast() const noexcept {
    return m_type == Type::LAST;
}


NAMESPACE_END(vexa)
