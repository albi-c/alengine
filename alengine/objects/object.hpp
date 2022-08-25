#pragma once

#include "graphics/render/drawable.hpp"
#include "graphics/render/material.hpp"

namespace ae {
    class Object : public Drawable {
    public:
        Material mat;

        inline Object(Material mat, int layer = 0)
            : Drawable(layer), mat(mat) {}
    };
};
