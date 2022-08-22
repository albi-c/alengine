#include "engine.hpp"

namespace ae::physics {
    void Engine::add(Collider* collider) {
        colliders.insert(collider);
    }
    void Engine::remove(Collider* collider) {
        colliders.erase(collider);
    }
};
