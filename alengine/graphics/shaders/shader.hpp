#pragma once

#include <string>
#include <memory>

#include "util/glm.hpp"

namespace ae {
    class Shader {
    public:
        Shader(const std::string& name);

        void use();

        void uniform(const std::string& name, int value);
        void uniform(const std::string& name, unsigned int value);
        void uniform(const std::string& name, float value);
        void uniform(const std::string& name, double value);

        void uniform(const std::string& name, const glm::vec2& value);
        void uniform(const std::string& name, const glm::vec3& value);
        void uniform(const std::string& name, const glm::vec4& value);

        void uniform(const std::string& name, const glm::mat4& value);

    private:
        unsigned int program;

        void init(const char* vertex_code, const char* fragment_code);
        void init(const std::string& vertex_code, const std::string& fragment_code);

        void prepare_set_uniform();
    };
};
