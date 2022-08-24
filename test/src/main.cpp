#include "alengine.hpp"

#include "objects/shapes/rect.hpp"
#include "objects/shapes/circle.hpp"
#include "objects/shapes/line.hpp"
#include "camera/camera.hpp"
#include "entity/player.hpp"

#include <iostream>

class Player : public ae::entity::Player {
public:
    ae::object::Rect obj;

    glm::vec2 pos;
    glm::vec2 size;

    Player(const glm::vec2& pos, const glm::vec2& size)
        : obj({{1.0f, 0.8f, 0.6f}}, &this->pos, &this->size), pos(pos), size(size), ae::entity::Player(obj) {}
    
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

class PlayerLine : public ae::entity::Player {
public:
    ae::object::Line obj;

    glm::vec2 p1;
    glm::vec2 p2;

    PlayerLine(const glm::vec2& p1, const glm::vec2& p2)
        : obj({{0.0f, 0.0f, 1.0f}}, &this->p1, &this->p2), p1(p1), p2(p2), ae::entity::Player(obj) {}
    
    void move(const glm::vec2& m) {
        p1 += m;
        p2 += m;
    }

    void moveX(float m) {
        p1.x += m;
        p2.x += m;
    }
    void moveY(float m) {
        p1.y += m;
        p2.y += m;
    }
};

class Game : public ae::Game {
public:
    Game()
        : ae::Game("Test Game"),
          player({50.0f, 250.0f}, {50.0f, 100.0f}),
          wall({{0.2f, 0.2f, 0.2f}}, {0.0f, 100.0f}, {1920.0f, 100.0f}),
          circle({{0.5f, 0.0f, 0.0f}}, {250.0f, 250.0f}, 50.0f),
          light({100.0f, 300.0f}, 500.0f, {2.0f, 1.8f, 1.7f}),
          light2({400.0f, 600.0f}, 150.0f, {1.8f, 0.0f, 2.0f}) {
        
        circle.layer = -1;
        
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
            player.draw();
            wall.draw();
            circle.draw();

            light.draw();
            light2.draw();
        });

        run();
    }
    
private:
    Player player;

    ae::object::Rect wall;
    ae::object::Circle circle;

    ae::Light light, light2;
};

int main() {
    Game game;

    return 0;
}
