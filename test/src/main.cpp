#include "alengine.hpp"

#include "objects/shapes/rect.hpp"
#include "objects/shapes/circle.hpp"
#include "camera/camera.hpp"
#include "entity/player.hpp"
#include "physics/engine.hpp"

#include <iostream>

int main() {
    ae::Game game("Test Game");

    ae::object::Rect player_rect({{0.0f, 1.0f, 1.0f}}, {0.0f, 0.0f}, {50.0f, 100.0f});
    player_rect.layer = 1;
    ae::entity::Player player(player_rect);

    ae::physics::HitboxCircle a({0.0f, 0.0f}, 4.0f);
    ae::physics::HitboxCircle b({5.0f, 5.0f}, 4.0f);
    auto c = a.collide(b);

    

    ae::Event::on<ae::EventKeyPress>([&](const ae::EventKeyPress& e) {
        if (e == ae::Key::ESCAPE && e == ae::Action::RELEASE) {
            game.stop();
        }
    });

    ae::Event::on<ae::EventUpdate>([&](const ae::EventUpdate& e) {
    });

    ae::Event::on<ae::EventDraw>([&](const ae::EventDraw&) {
        ae::object::Rect({{1.0f, 0.0f, 0.0f}}, glm::vec2(game.time() * 10.0f), {100.0f, 100.0f}).draw();
        ae::Renderer::render(player);
    });

    game.run();

    return 0;
}
