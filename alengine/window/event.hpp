#pragma once

#include "event/event.hpp"
#include "mouse.hpp"
#include "keyboard.hpp"

#include "better_enum.hpp"

namespace ae {
    struct EventWindowResize : public Event {
        int width, height;

        EventWindowResize(int width, int height) : width(width), height(height) {}
    };

    struct EventMouseMove : public Event {
        int x, y;

        EventMouseMove(int x, int y) : x(x), y(y) {}
        EventMouseMove(double x, double y) : x(x), y(y) {}
    };

    BETTER_ENUM(Action, int,
        RELEASE = 0,
        PRESS = 1
    );

    struct EventMouseClick : public Event {
        MouseButton button;
        Action action;

        EventMouseClick(MouseButton button, Action action) : button(button), action(action) {}
        EventMouseClick(int button, int action)
            : button(MouseButton::_from_integral(button)), action(Action::_from_integral(action)) {}
        
        bool operator==(const MouseButton& other) const {
            return button == other;
        }
        bool operator==(const Action& other) const {
            return action == other;
        }
    };

    struct EventKeyPress : public Event {
        Key key;
        Action action;

        EventKeyPress(Key key, Action action) : key(key), action(action) {}
        EventKeyPress(int key, int action)
            : key(Key::_from_integral(key)), action(Action::_from_integral(action)) {}

        bool operator==(const Key& other) const {
            return key == other;
        }
        bool operator==(const Action& other) const {
            return action == other;
        }
    };
};
