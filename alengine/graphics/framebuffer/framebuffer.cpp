#include "framebuffer.hpp"

namespace ae {
    Framebuffer::~Framebuffer() {
        destroy();
    }

    void Framebuffer::init(int width, int height, bool depth_only) {
        if (initialized)
            return;
        
        this->width = width;
        this->height = height;

        glGenFramebuffers(1, &fbo);

        bind();

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        if (depth_only) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        }

        unbind();
    }
    void Framebuffer::destroy() {
        if (initialized) {
            initialized = false;
            glDeleteTextures(1, &texture);
            glDeleteFramebuffers(1, &fbo);
        }
    }

    void Framebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }
    void Framebuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint Framebuffer::tex() {
        return texture;
    }
};
