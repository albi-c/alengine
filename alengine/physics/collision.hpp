#pragma once

#include "util/glm.hpp"

namespace ae::physics {
    struct CollisionPoints {
        bool collided;
        glm::vec2 a, b;
        glm::vec2 normal;
        float depth;
    };

    class ColliderCircle;
    class ColliderAABB;
    class Collider {
    public:
        Collider(const glm::vec2& pos);
        ~Collider();

        int layer = 0;

        glm::vec2 pos;
        glm::vec2 vel;

        virtual CollisionPoints collide(const Collider& collider) const =0;
        virtual CollisionPoints collide(const ColliderCircle& collider) const =0;
        virtual CollisionPoints collide(const ColliderAABB& collider) const =0;
    };

    class ColliderCircle : public Collider {
    public:
        float rad;

        ColliderCircle(const glm::vec2& pos, float rad);

        virtual CollisionPoints collide(const Collider& collider) const;
        virtual CollisionPoints collide(const ColliderCircle& collider) const;
        virtual CollisionPoints collide(const ColliderAABB& collider) const;
    };

    class ColliderAABB : public Collider {
    public:
        glm::vec2 size;

        ColliderAABB(const glm::vec2& pos, const glm::vec2& size);

        virtual CollisionPoints collide(const Collider& collider) const;
        virtual CollisionPoints collide(const ColliderCircle& collider) const;
        virtual CollisionPoints collide(const ColliderAABB& collider) const;
    };
};
