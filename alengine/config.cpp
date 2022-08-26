#include "config.hpp"

namespace ae {
    static consteval bool opengl_debug_enabled(int version_major, int version_minor) {
        return (version_major * 10 + version_minor) >= 43;
    }

    const int OPENGL_VERSION_MAJOR = 3;
    const int OPENGL_VERSION_MINOR = 3;

    const bool OPENGL_DEBUG = opengl_debug_enabled(OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);
};
