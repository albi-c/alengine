#pragma once

#include <vector>

#include "vertex.hpp"
#include "light/light.hpp"

namespace ae {
    class Renderable {
    public:
        int layer = 0;

        inline Renderable(int layer = 0)
            : layer(layer) {}

        virtual std::vector<Vertex> vertices() const =0;
        virtual const Light* light() const { return nullptr; }
    };
};
