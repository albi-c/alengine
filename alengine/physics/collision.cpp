#include "collision.hpp"

#include "engine.hpp"

namespace ae::physics {
    Collider::Collider(const glm::vec2& pos)
        : pos(pos) {
        Engine::add(this);
    }
    Collider::~Collider() {
        Engine::remove(this);
    }

    ColliderCircle::ColliderCircle(const glm::vec2& pos, float rad)
        : Collider(pos), rad(rad) {}

    CollisionPoints ColliderCircle::collide(const Collider& collider) const {
        if (layer != collider.layer)
            return {false};
        
        return collider.collide(*this);
    }
    CollisionPoints ColliderCircle::collide(const ColliderCircle& collider) const {
        if (layer != collider.layer)
            return {false};
        
        float distance = glm::distance(pos, collider.pos);
        float depth = rad + collider.rad - distance;
        if (depth > 0.0f) {
            glm::vec2 dir = collider.pos - pos;
            glm::vec2 a = pos + dir - depth;
            glm::vec2 b = collider.pos - dir + depth;

            return {
                true,
                a, b,
                glm::normalize(a - b),
                depth
            };
        }
        return {false};
    }
    CollisionPoints ColliderCircle::collide(const ColliderAABB& collider) const {
        if (layer != collider.layer)
            return {false};
    }

    ColliderAABB::ColliderAABB(const glm::vec2& pos, const glm::vec2& size)
        : Collider(pos), size(size) {}

    CollisionPoints ColliderAABB::collide(const Collider& collider) const {
        if (layer != collider.layer)
            return {false};
        
        return collider.collide(*this);
    }
    CollisionPoints ColliderAABB::collide(const ColliderCircle& collider) const {
        if (layer != collider.layer)
            return {false};
        
        
    }
    CollisionPoints ColliderAABB::collide(const ColliderAABB& collider) const {
        if (layer != collider.layer)
            return {false};
    }
};
