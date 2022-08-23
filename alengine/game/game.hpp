#pragma once

#include <string>
#include <memory>

#include "window/window.hpp"

namespace ae {
    struct EventUpdate : public Event {
        float dt;

        EventUpdate(float dt) : dt(dt) {}
    };
    struct EventDraw : public Event {};

    class Game {
    public:
        Game(const std::string& name, int window_flags = WindowFlags::ALLOW_FULLSCREEN);
        ~Game();

        void run();

        void stop();

        float time();
    };
};
