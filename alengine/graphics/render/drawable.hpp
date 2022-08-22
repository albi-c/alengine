#pragma once

#include "vertex.hpp"

#include <vector>

namespace ae {
    class Drawable {
    public:
        int layer = 0;

        inline Drawable(int layer = 0)
            : layer(layer) {}

        virtual std::vector<Vertex> vertices() const =0;
    };
};
