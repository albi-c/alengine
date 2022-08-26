#include "alengine.hpp"

#include "camera/camera.hpp"

#include <iostream>

class Player : public ae::Rect {
public:
    Player(const glm::vec2& pos, const glm::vec2& size)
        : Rect({{1.0f, 1.0f, 1.0f}, std::make_shared<ae::Texture>(new ae::Texture("../res/box.png")), {1.0f, 2.0f}}, pos, size) {}
    
    void move(const glm::vec2& m) {
        pos += m;
    }

    void moveX(float m) {
        pos.x += m;
    }
    void moveY(float m) {
        pos.y += m;
    }
};

class Game : public ae::Game {
public:
    Game()
        : ae::Game("Test Game"),
          player({50.0f, 250.0f}, {50.0f, 100.0f}),
          wall({{0.5f, 0.5f, 0.5f}}, {0.0f, 100.0f}, {100.0f, 100.0f}),
          circle({{1.0f, 0.0f, 0.0f}}, {250.0f, 250.0f}, 50.0f),
          floor({{0.1f, 0.1f, 0.1f}, std::make_shared<ae::Texture>(new ae::Texture("../res/box.png")), {1.0f, 1.0f}}, {0.0f, 0.0f}, {100.0f, 100.0f}),
          light({100.0f, 300.0f}, 200.0f, {1.0, 1.0, 1.0}),
          light2({400.0f, 600.0f}, 50.0f, {1.0, 0.0, 1.0}) {
        
        circle.layer = -1;

        floor.layer = -2;
        
        ae::Event::on<ae::EventWindowResize>([&](const ae::EventWindowResize& e) {
            wall.size.x = e.width;

            floor.size = glm::vec2(e.width, e.height) + glm::vec2(128.0f, 128.0f);
            floor.mat.texture_repeat = floor.size / 128.0f;
        });

        ae::Event::on<ae::EventKeyPress>([&](const ae::EventKeyPress& e) {
            if (e == ae::Key::ESCAPE && e == ae::Action::RELEASE) {
                stop();
            }
        });

        ae::Event::on<ae::EventUpdate>([&](const ae::EventUpdate& e) {
            bool movedX = false;
            bool movedY = false;
            glm::vec2 move = glm::vec2(0.0f, -0.5f);
            if (e.keys[ae::Key::W]) {
                move.y += 1.0f;
                movedY = !movedY;
            }
            if (e.keys[ae::Key::A]) {
                move.x -= 1.0f;
                movedX = !movedX;
            }
            if (e.keys[ae::Key::S]) {
                move.y -= 1.0f;
                movedY = !movedY;
            }
            if (e.keys[ae::Key::D]) {
                move.x += 1.0f;
                movedX = !movedX;
            }
            
            if (move != glm::vec2(0.0f, 0.0f)) {
                move = glm::normalize(move) * e.dt * 500.0f;
                
                player.moveX(move.x);
                while (player.collide(wall) || player.collide(circle)) {
                    player.moveX(-(move.x * 0.125));
                }

                player.moveY(move.y);
                while (player.collide(wall) || player.collide(circle)) {
                    player.moveY(-(move.y * 0.125));
                }
            }

            floor.pos -= ae::Camera::pos;
            floor.pos += (glm::ivec2)ae::Camera::pos & 0x7f;

            ae::Camera::pos = player.pos - ae::Window::size() / 2.0f;

            floor.pos -= (glm::ivec2)ae::Camera::pos & 0x7f;
            floor.pos += ae::Camera::pos;
        });

        ae::Event::on<ae::EventDraw>([&](const ae::EventDraw&) {
            ae::Renderer::render(player);
            ae::Renderer::render(wall);
            ae::Renderer::render(circle);

            ae::Renderer::render(floor);

            ae::Renderer::render(light);
            ae::Renderer::render(light2);
        });

        run();
    }
    
private:
    Player player;

    ae::Rect wall;
    ae::Circle circle;

    ae::Rect floor;

    ae::Light light, light2;
};

int main() {
    Game game;

    return 0;
}
