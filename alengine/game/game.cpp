#include "game.hpp"

namespace ae {
    Game::Game(const std::string& name, int window_flags) {
        Window::init(name, window_flags);
    }
    Game::~Game() {
        Window::destroy();
    }

    void Game::run() {
        bool keys[Key::_LAST_KEY + 1];

        while (Window::update()) {
            Window::get_keys(keys);
            EventUpdate{Window::get_dt(), keys}.fire();

            Window::render_start();

            EventDraw{}.fire();

            Window::render_end();
        }
    }

    void Game::stop() {
        Window::close();
    }

    float Game::time() {
        return (float)glfwGetTime();
    }
};
