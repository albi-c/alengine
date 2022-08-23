#include "window.hpp"

#include <iostream>

#include "config.hpp"
#include "graphics/opengl.hpp"
#include "gl_debug.inl"
#include "util/util.hpp"
#include "graphics/render/renderer.hpp"
#include "camera/camera.hpp"

namespace ae {
    void Window::init(const std::string& title, int flags) {
        if (initialized)
            return;
        
        Window::flags = flags;
        
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);        
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 16);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        glfwWindowHint(GLFW_RED_BITS, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_GREEN_BITS, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_BLUE_BITS, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
        if (OPENGL_DEBUG) {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        }

        monitor = glfwGetPrimaryMonitor();
        fullscreen = flags & WindowFlags::FULLSCREEN;
        if (fullscreen) {
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, NULL);
        } else {
           window = glfwCreateWindow(1280, 720, title.c_str(), NULL, NULL);
        }
        if (window == NULL) {
            log::e("Failed to create window");
        }
        glfwMakeContextCurrent(window);
        
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            log::e("Failed to initialize OpenGL");
        }

        initialized = true;

        glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)(&Window::callback_framebuffer_resize));

        glfwSetCursorPosCallback(window, (GLFWcursorposfun)(&Window::callback_mouse_move));
        glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)(&Window::callback_mouse_click));
        glfwSetKeyCallback(window, (GLFWkeyfun)(&Window::callback_key_press));

        if (OPENGL_DEBUG) {
            int flags;
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(glDebugOutput, nullptr);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            }
        }

        Renderer::init();
        Camera::init();
    }
    void Window::destroy() {
        if (initialized) {
            initialized = false;
            Renderer::destroy();
            glfwDestroyWindow(window);
            window = nullptr;
        }
    }

    bool Window::update() {
        static double last_time = 0.0;

        glfwPollEvents();

        double time = glfwGetTime();
        dt = time - last_time;
        last_time = time;

        return !glfwWindowShouldClose(window);
    }
    void Window::render_start() {
        Renderer::render_start();
    }
    void Window::render_end() {
        Renderer::render_end();

        glfwSwapBuffers(window);
    }

    void Window::close() {
        glfwSetWindowShouldClose(window, true);
    }

    float Window::get_dt() {
        return (float)dt;
    }

    void Window::get_keys(bool* keys) {
        for (int i = 0; i < GLFW_KEY_LAST; i++) {
            keys[i] = glfwGetKey(window, i);
        }
    }

    void Window::callback_framebuffer_resize(GLFWwindow* glfw_window, int width, int height) {
        Window::width = width;
        Window::height = height;

        EventWindowResize{width, height}.fire();

        Renderer::resize(width, height);
        Camera::resize(width, height);
    }

    void Window::callback_mouse_move(GLFWwindow* glfw_window, double x, double y) {
        EventMouseMove{x, y}.fire();
    }
    void Window::callback_mouse_click(GLFWwindow* glfw_window, int button, int action, int mods) {
        EventMouseClick{button, action}.fire();
    }
    void Window::callback_key_press(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT)
            return;
        
        EventKeyPress{key, action}.fire();

        if (flags & WindowFlags::ALLOW_FULLSCREEN && key == GLFW_KEY_F11 && action == GLFW_PRESS) {
            if (fullscreen) {
                glfwSetWindowMonitor(window, NULL, 0, 50, width, height - 100, 0);
            } else {
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
            fullscreen = !fullscreen;
        }
    }
};
