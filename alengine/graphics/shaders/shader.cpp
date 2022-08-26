#include "shader.hpp"

#include <map>
#include <utility>

#include "graphics/opengl.hpp"
#include "util/util.hpp"

static const std::map<std::string, std::pair<const char*, const char*>> BUILTIN_SHADERS = {
    {"main", {R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 model;

uniform float layer;

uniform vec2 texture_repeat;

void main() {
    gl_Position = transform * model * vec4(aPos, layer, 1.0);

    TexCoord = aTex * texture_repeat;
}
)", R"(
#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool texture_enabled;

uniform vec3 color;

void main() {
    vec3 col = color;

    if (texture_enabled) {
        col *= texture(texture1, TexCoord).rgb;
    }

    FragColor = vec4(col, 1.0);
}
)"}}, {"post", {R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform mat4 transform;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);

    TexCoord = aTex;
}
)", R"(
#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex_main;
uniform sampler2D tex_light;

void main() {
    vec3 color = texture(tex_main, TexCoord).rgb;
    vec3 light = texture(tex_light, TexCoord).rgb;

    vec3 o = color * (light + 0.05) + light * 0.1 + 0.003;
    o /= o + 1.0;
    o = pow(o, vec3(1.0 / 1.8));

    FragColor = vec4(o, 1.0);
}
)"}}, {"light", {R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 FragPos;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0);

    FragPos = vec3(view * vec4(aPos, 0.0, 1.0)).xy;
    TexCoord = aTex;
}
)", R"(
#version 330 core
in vec2 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec2 light_pos;
uniform float light_range;
uniform vec3 light_color;

void main() {
    vec3 light = vec3(0.0);

    float d = distance(light_pos, FragPos);
    if (d <= light_range) {
        light = (light_color * pow(light_range - d, 2.0) / pow(light_range, 2.0));
    }

    FragColor = vec4(light, 1.0);
}
)"}}
};

namespace ae {
    Shader::Shader(const std::string& name) {
        init(BUILTIN_SHADERS.at(name).first, BUILTIN_SHADERS.at(name).second);
    }

    void Shader::use() {
        glUseProgram(program);
    }

    void Shader::uniform(const std::string& name, int value) {
        prepare_set_uniform();
        glUniform1i(glGetUniformLocation(program, name.c_str()), value);
    }
    void Shader::uniform(const std::string& name, GLuint value) {
        prepare_set_uniform();
        glUniform1i(glGetUniformLocation(program, name.c_str()), value);
    }
    void Shader::uniform(const std::string& name, float value) {
        prepare_set_uniform();
        glUniform1f(glGetUniformLocation(program, name.c_str()), value);
    }
    void Shader::uniform(const std::string& name, double value) {
        prepare_set_uniform();
        glUniform1f(glGetUniformLocation(program, name.c_str()), (float)value);
    }

    void Shader::uniform(const std::string& name, const glm::vec2& value) {
        prepare_set_uniform();
        glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }
    void Shader::uniform(const std::string& name, const glm::vec3& value) {
        prepare_set_uniform();
        glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }
    void Shader::uniform(const std::string& name, const glm::vec4& value) {
        prepare_set_uniform();
        glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
    }

    void Shader::uniform(const std::string& name, const glm::mat4& value) {
        prepare_set_uniform();
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::init(const char* vertex_code, const char* fragment_code) {
        GLuint vertex_shader, fragment_shader;
        int success;
        char infoLog[2048];

        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code, NULL);
        glCompileShader(vertex_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader, 2048, NULL, infoLog);
            log::e("Failed to compile vertex shader | " + std::string(infoLog));
        }

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_code, NULL);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, 2048, NULL, infoLog);
            log::e("Failed to compile fragment shader | " + std::string(infoLog));
        }

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 2048, NULL, infoLog);
            log::e("Failed to link shaders | " + std::string(infoLog));
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
    void Shader::init(const std::string& vertex_code, const std::string& fragment_code) {
        init(vertex_code.c_str(), fragment_code.c_str());
    }

    void Shader::prepare_set_uniform() {
        glUseProgram(program);
    }
};

