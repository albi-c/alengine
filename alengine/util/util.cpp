#include "util.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace ae {
    namespace time {
        const std::string TIME_FORMAT("%Y-%m-%d %H:%M:%S");

        std::string get_time() {
            std::ostringstream oss;
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            oss << std::put_time(&tm, TIME_FORMAT.c_str());
            return oss.str();
        };
    };

    namespace log {
        static std::string construct_string(LogLevel level, const std::string& message) {
            std::ostringstream oss;
            oss <<
                time::get_time() <<
                " [" <<
                level._to_string()[0] <<
                "] " <<
                message;
            return oss.str();
        }

        void log(LogLevel level, const std::string& message) {
            if ((int)level < (int)LogLevel::ERROR) {
                std::cout << construct_string(level, message) << "\n";
            } else {
                std::cerr << construct_string(level, message) << "\n";
            }
        }
    };
};
