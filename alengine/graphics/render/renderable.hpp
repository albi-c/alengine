#pragma once

#include <vector>

#include "vertex.hpp"

namespace ae {
    class Renderable {
    public:
        int layer = 0;

        inline Renderable(int layer = 0)
            : layer(layer) {}

        virtual std::vector<Vertex> vertices() const =0;
    };
};
