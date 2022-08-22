#pragma once

#include "shape.hpp"

namespace ae::object {
    class Rect : public Shape {
    public:
        glm::vec2 pos;
        glm::vec2 size;
        Material mat;

        Rect();
        Rect(const Material& mat);
        Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size);

        virtual std::vector<Vertex> vertices() const;
    };
};
