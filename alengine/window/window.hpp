#pragma once

#include <string>

#include "graphics/glfw.hpp"
#include "event.hpp"

#include "better_enum.hpp"

namespace ae {
    BETTER_ENUM(WindowFlags, int,
        ALLOW_FULLSCREEN = 0x1,
        FULLSCREEN = 0x2
    );

    class Window {
    public:
        static void init(const std::string& title, int flags);
        static void destroy();

        static bool update();
        static void render_start();
        static void render_end(); 

        static void close();

        static float get_dt();

        static void get_keys(bool* keys);
    
    private:
        static inline GLFWwindow* window;
        static inline GLFWmonitor* monitor;
        static inline bool initialized = false;

        static inline int width, height;

        static inline double dt;

        static inline int flags;
        static inline bool fullscreen;

        static void callback_framebuffer_resize(GLFWwindow* glfw_window, int width, int height);
        static void callback_mouse_move(GLFWwindow* glfw_window, double x, double y);
        static void callback_mouse_click(GLFWwindow* glfw_window, int button, int action, int mods);
        static void callback_key_press(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
    };
};
