#pragma once

#include "util/glm.hpp"

namespace ae {
    class Camera {
    public:
        static inline glm::vec2 pos;

        static void init();

        static void resize(int width, int height);

        static glm::mat4 projection();
        static glm::mat4 view(bool inv = false);
    
    private:
        static inline int width, height;
    };
};
