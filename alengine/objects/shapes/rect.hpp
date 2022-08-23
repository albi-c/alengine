#pragma once

#include "shape.hpp"
#include "physics/collision.hpp"

namespace ae::object {
    class Rect : public Shape, public physics::HitboxAABB {
    public:
        Material mat;

        Rect();
        Rect(const Material& mat);
        Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size);
        Rect(const Material& mat, glm::vec2* pos, glm::vec2* size);

        virtual std::vector<Vertex> vertices() const;
    };
};
