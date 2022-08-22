#pragma once

#include "vertex.hpp"

#include <vector>

namespace ae {
    class Drawable {
    public:
        virtual std::vector<Vertex> vertices() const =0;
        virtual int num_vectices() const =0;
    };
};
