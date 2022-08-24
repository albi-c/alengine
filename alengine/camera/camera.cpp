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
        // return glm::ortho(0.0f, width / zoom, 0.0f, height / zoom, -10.0f, 10.0f);
        return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -10.0f, 10.0f);
    }
    glm::mat4 Camera::view() {
        return glm::translate(glm::mat4(1.0), -glm::vec3(pos, 0.0f));
    }
};
