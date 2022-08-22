#include "alengine.hpp"

#include <iostream>

int main() {
    ae::Game game("Test Game");

    ae::Event::on<ae::EventKeyPress>([&](const ae::EventKeyPress& e) {
        if (e == ae::Key::ESCAPE && e == ae::Action::RELEASE) {
            game.stop();
        }
    });

    ae::Event::on<ae::EventUpdate>([&](const ae::EventUpdate& e) {
    });

    ae::Event::on<ae::EventDraw>([&](const ae::EventDraw&) {
    });

    game.run();

    return 0;
}
