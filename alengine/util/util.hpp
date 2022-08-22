#pragma once

#include <string>

#include "better_enum.hpp"

namespace ae {
    namespace time {
        extern const std::string TIME_FORMAT;

        std::string get_time();
    };

    namespace log {
        BETTER_ENUM(LogLevel, int,
            DEBUG = 0,
            INFO,
            WARN,
            ERROR
        );

        void log(LogLevel level, const std::string& message);

        inline void d(const std::string& message) {
            log(LogLevel::DEBUG, message);
        }
        inline void i(const std::string& message) {
            log(LogLevel::INFO, message);
        }
        inline void w(const std::string& message) {
            log(LogLevel::WARN, message);
        }
        inline void e(const std::string& message) {
            log(LogLevel::ERROR, message);
        }
    };
};
