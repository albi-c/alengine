#pragma once

#include "shape.hpp"
#include "physics/collision.hpp"

namespace ae::object {
    class Circle : public Shape, public physics::HitboxCircle {
    public:
        Material mat;

        Circle();
        Circle(const Material& mat);
        Circle(const Material& mat, const glm::vec2& pos, float rad);
        Circle(const Material& mat, glm::vec2* pos, float* rad);

        virtual std::vector<Vertex> vertices() const;
    };
};
