#pragma once
#include <functional>
#include <vector>

namespace engine
{
    namespace gameplay
    {
        // Simple event system for broadcasting notifications to multiple listeners.
        // Usage: Observer<void()> for signals, Observer<void(const T&)> for value events.
        template<typename... Args>
        class Observer
        {
        public:
            using Callback = std::function<void(Args...)>;

            // Calls all registered callbacks with the given arguments.
            void notify(Args... args)
            {
                for (const auto& callback : _callbacks)
                {
                    callback(args...);
                }
            }

            // Registers a new callback to be notified.
            void addCallback(Callback callback)
            {
                _callbacks.push_back(callback);
            }

        private:
            std::vector<Callback> _callbacks; // List of registered listeners.
        };
    }
}