#pragma once

#include "renderable.hpp"

namespace ae {
    class Drawable : public Renderable {
    public:
        inline Drawable(int layer = 0)
            : Renderable(layer) {}
    };
};
