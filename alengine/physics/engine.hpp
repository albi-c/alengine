#pragma once

#include <unordered_set>

#include "util/glm.hpp"
#include "collision.hpp"

namespace ae::physics {
    class Engine {
    public:
        static inline glm::vec2 gravity;

        static void add(Hitbox* collider);
        static void remove(Hitbox* collider);
    
    private:
        static inline std::unordered_set<Hitbox*> colliders;
    };
};
