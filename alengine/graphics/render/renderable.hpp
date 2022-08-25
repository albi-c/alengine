#pragma once

#include "graphics/texture/texture.hpp"

namespace ae {
    class Renderable {
    public:
        int layer = 0;

        inline Renderable(int layer = 0)
            : layer(layer) {}
    };
};
