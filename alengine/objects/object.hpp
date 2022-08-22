#pragma once

#include "graphics/render/drawable.hpp"
#include "graphics/render/renderer.hpp"

namespace ae::object {
    class Object : public Drawable {
    public:
        inline Object(int layer = 0)
            : Drawable(layer) {}

        inline void draw() const {
            Renderer::render(*this);
        }
    };
};
