#include "alengine.hpp"

#include "camera/camera.hpp"

#include <iostream>

class Player : public ae::Rect {
public:
    ae::Rect obj;

    glm::vec2 pos;
    glm::vec2 size;

    Player(const glm::vec2& pos, const glm::vec2& size)
        : pos(pos), size(size), Rect({{1.0f, 1.0f, 1.0f}}, &this->pos, &this->size) {}
    
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
          wall({{0.5f, 0.5f, 0.5f}}, {0.0f, 100.0f}, {1920.0f, 100.0f}),
          circle({{1.0f, 0.0f, 0.0f}}, {250.0f, 250.0f}, 50.0f),
          light({100.0f, 300.0f}, 200.0f, {1.0, 1.0, 1.0}),
          light2({400.0f, 600.0f}, 50.0f, {1.0, 0.0, 1.0}) {
        
        circle.layer = -1;

        // for (int i = 0; i < 10; i++) {
        //     for (int j = 0; j < 10; j++) {
        //         circles.push_back(ae::Circle({{1.0f - (i / 1000.0f), i / 1000.0f, 0.0f}}, {i * 10.0f, j * 10.0f}, 5.0f));
        //     }
        // }
        
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
            glm::vec2 move = glm::vec2(0.0f);
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
            
            if (movedX || movedY) {
                move = glm::normalize(move) * e.dt * 500.0f;

                player.moveX(move.x);
                if (player.obj.collide(wall) || player.obj.collide(circle)) {
                    player.moveX(-move.x);
                }

                player.moveY(move.y);
                if (player.obj.collide(wall) || player.obj.collide(circle)) {
                    player.moveY(-move.y);
                }
            }

            ae::Camera::pos = player.pos - ae::Window::size() / 2.0f;
        });

        ae::Event::on<ae::EventDraw>([&](const ae::EventDraw&) {
            ae::Renderer::render(player.obj);
            ae::Renderer::render(wall);
            ae::Renderer::render(circle);

            ae::Renderer::render(light);
            ae::Renderer::render(light2);
        });

        run();
    }
    
private:
    Player player;

    ae::Rect wall;
    ae::Circle circle;

    // std::vector<ae::Circle> circles;

    ae::Light light, light2;
};

int main() {
    Game game;

    return 0;
}
