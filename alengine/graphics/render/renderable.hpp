#pragma once

#include <vector>

#include "vertex.hpp"
#include "light/light.hpp"
#include "graphics/texture/texture.hpp"

namespace ae {
    class Renderable {
    public:
        int layer = 0;

        inline Renderable(int layer = 0)
            : layer(layer) {}

        virtual std::vector<Vertex> vertices() const {}

        virtual std::vector<TexVertex> vertices_tex() const {}
        virtual const Texture* texture() const {}
    };
};
