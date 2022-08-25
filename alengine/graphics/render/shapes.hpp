#pragma once

#include "objects/object.hpp"
#include "material.hpp"
#include "objects/shapes.hpp"

namespace ae {
    class RendererShape : public Object {
    public:
        inline RendererShape(Material mat, int layer = 0)
            : Object(mat) {}
    };

    class RendererRect : public RendererShape {
    public:
        glm::vec2 pos;
        glm::vec2 size;

        RendererRect(const Rect& rect);
    };

    class RendererLine : public RendererShape {
    public:
        glm::vec2 p1;
        glm::vec2 p2;

        RendererLine(const Line& line);
    };

    class RendererCircle : public RendererShape {
    public:
        glm::vec2 pos;
        float rad;

        RendererCircle(const Circle& circle);
    };
};
