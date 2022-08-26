#pragma once

#include <string>

#include "graphics/opengl.hpp"

namespace ae {
    class Texture {
    public:
        Texture(Texture* other);
        Texture(const std::string& filename);
        ~Texture();

        void bind() const;
    
    private:
        GLuint texture;
    };
};
