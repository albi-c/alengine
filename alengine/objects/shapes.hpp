#pragma once

#include "objects/object.hpp"
#include "physics/hitbox.hpp"
#include "graphics/render/material.hpp"

namespace ae {
    class Shape : public Object {
    public:
        inline Shape(Material mat, int layer = 0)
            : Object(mat) {}
    };

    class Rect : public Shape, public HitboxAABB {
    public:
        Rect(const Material& mat = {});
        Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size);
        Rect(const Material& mat, glm::vec2* pos, glm::vec2* size);
    };

    class Line : public Shape, public HitboxLine {
    public:
        Line(const Material& mat = {});
        Line(const Material& mat, const glm::vec2& p1, const glm::vec2& p2);
        Line(const Material& mat, glm::vec2* p1, glm::vec2* p2);
    };

    class Circle : public Shape, public HitboxCircle {
    public:
        Circle(const Material& mat = {});
        Circle(const Material& mat, const glm::vec2& pos, float rad);
        Circle(const Material& mat, glm::vec2* pos, float* rad);
    };
};
