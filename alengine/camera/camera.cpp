#include "camera.hpp"

namespace ae {
    void Camera::init() {
        resize(1, 1);
    }

    void Camera::resize(int width, int height) {
        Camera::width = width;
        Camera::height = height;
    }

    glm::mat4 Camera::projection() {
        return glm::ortho(0.0f, width / zoom, 0.0f, height / zoom, -10.0f, 10.0f);
    }
    glm::mat4 Camera::view() {
        return glm::translate(glm::mat4(), -glm::vec3(pos, 0.0f));
    }
};
