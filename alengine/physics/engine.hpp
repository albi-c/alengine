#pragma once

#include <unordered_set>

#include "util/glm.hpp"
#include "collision.hpp"

namespace ae::physics {
    class Engine {
    public:
        static inline glm::vec2 gravity;

        static void add(Collider* collider);
        static void remove(Collider* collider);
    
    private:
        static inline std::unordered_set<Collider*> colliders;
    };
};
