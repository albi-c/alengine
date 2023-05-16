#include "alengine.hpp"

#include "camera/camera.hpp"
#include "graphics/texture/texture.hpp"

#include <iostream>
#include <memory>

class Player : public ae::Rect {
public:
    Player(const glm::vec2& pos, const glm::vec2& size)
        : Rect({{1.0f, 1.0f, 1.0f}}, pos, size) {}
    
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
          wall({glm::vec3(1.0f), std::make_shared<ae::Texture>("../res/box.png"), {19.2f, 1.0f}}, {0.0f, 100.0f}, {1920.0f, 100.0f}),
          circle({glm::vec3(1.0f), std::make_shared<ae::Texture>("../res/box.png")}, {250.0f, 250.0f}, 50.0f),
          light({100.0f, 300.0f}, 200.0f, {1.0, 1.0, 1.0}),
          light2({400.0f, 600.0f}, 50.0f, {1.0, 0.0, 1.0}) {
        
        circle.layer = -1;

        int i = 0;
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                circles[i++] = ae::Circle({{x / 10.0f, y / 10.0f, 0.0f}}, {x * 50.0f, y * 50.0f}, 15.0f);
            }
        }

        i = 0;
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                rects[i++] = ae::Rect({{x / 10.0f, y / 10.0f, 0.0f}}, {x * 50.0f + 1000.0f, y * 50.0f}, {15.0f, 20.0f});
            }
        }
        
        ae::Event::on<ae::EventWindowResize>([&](const ae::EventWindowResize& e) {
            wall.size.x = e.width;
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
            
            if (move != glm::vec2(0.0f)) {
                move = glm::normalize(move) * e.dt * 500.0f;

                player.moveX(move.x);
                if (player.collide(wall) || player.collide(circle)) {
                    player.moveX(-move.x);
                }

                player.moveY(move.y);
                if (player.collide(wall) || player.collide(circle)) {
                    player.moveY(-move.y);
                }
            }

            ae::Camera::pos = player.pos - ae::Window::size() / 2.0f;
        });

        ae::Event::on<ae::EventDraw>([&](const ae::EventDraw&) {
            ae::Renderer::render(player);
            ae::Renderer::render(wall);
            ae::Renderer::render(circle);

            ae::Renderer::render(circles);
            ae::Renderer::render(rects);

            ae::Renderer::render(light);
            ae::Renderer::render(light2);
        });

        run();
    }
    
private:
    Player player;

    ae::Rect wall;
    ae::Circle circle;

    std::map<int, ae::Circle> circles;
    std::map<int, ae::Rect> rects;

    ae::Light light, light2;
};

int main() {
    Game game;

    return 0;
}
