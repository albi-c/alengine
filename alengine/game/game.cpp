#include "game.hpp"

namespace ae {
    Game::Game(const std::string& name, int window_flags) {
        Window::init(name, window_flags);
    }
    Game::~Game() {
        Window::destroy();
    }

    void Game::run() {
        while (Window::update()) {
            EventUpdate{Window::get_dt()}.fire();

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
