#pragma once

#include "shape.hpp"
#include "physics/collision.hpp"

namespace ae::object {
    class Line : public Shape, public physics::HitboxLine {
    public:
        Material mat;

        Line();
        Line(const Material& mat);
        Line(const Material& mat, const glm::vec2& p1, const glm::vec2& p2);
        Line(const Material& mat, glm::vec2* p1, glm::vec2* p2);

        virtual std::vector<Vertex> vertices() const;
    };
};
