#include "engine.hpp"

namespace ae::physics {
    void Engine::add(Hitbox* collider) {
        colliders.insert(collider);
    }
    void Engine::remove(Hitbox* collider) {
        colliders.erase(collider);
    }
};
