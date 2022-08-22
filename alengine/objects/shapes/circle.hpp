#pragma once

#include "shape.hpp"

namespace ae::object {
    class Circle : public Shape {
    public:
        glm::vec2 pos;
        float rad;
        Material mat;

        Circle();
        Circle(const Material& mat);
        Circle(const Material& mat, const glm::vec2& pos, float rad);

        virtual std::vector<Vertex> vertices() const;
    };
};
