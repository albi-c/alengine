#pragma once

#include "renderer.hpp"
#include "renderable.hpp"

namespace ae {
    class Drawable : public Renderable {
    public:
        inline Drawable(int layer = 0)
            : Renderable(layer) {}
        
        inline void draw(const glm::vec2& translate = glm::vec2(0.0f)) const {
            Renderer::render(*this, translate);
        }
    };
};
