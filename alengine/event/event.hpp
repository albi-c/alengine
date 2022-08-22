#pragma once

#include <functional>
#include <queue>
#include <map>
#include <vector>
#include <type_traits>

namespace ae {
    template <typename T>
    using event_handler_t = std::function<void(const T&)>;

    class Event;
    using event_handler_generic_t = std::function<void(const Event&)>;

    class Event {
    public:
        template <typename T>
        static void on(event_handler_t<T> handler) {
            handlers[typeid(T).hash_code()].push_back([&](const Event& e) {
                handler(static_cast<const T&>(e));
            });
        }

        virtual void fire() const {
            for (auto& handler : handlers[typeid(*this).hash_code()]) {
                handler(*this);
            }
        }
    
    private:
        static inline std::map<std::size_t, std::vector<event_handler_generic_t>> handlers;
    };
};
