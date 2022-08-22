#pragma once

#include "drawable.hpp"

#include <memory>

namespace ae {
    class Renderer {
    public:
        static void init();

        static void render_start();
        static void render(std::shared_ptr<Drawable>& object);
        static void render_end();

        static void resize(int width, int height);
    
    private:
        static inline int width, height;

        static inline std::vector<std::shared_ptr<Drawable>> objects;
    };
};
