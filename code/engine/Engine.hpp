#pragma once
#include <string>
#include <memory>
#include "EngineContext.hpp"

namespace engine
{
    class Engine
    {
    public:
        Engine();
        ~Engine() = default;

        // Loads engine configuration from an XML file (e.g., start map).
        void loadConfiguration();

        // Main loop: runs the game until exit is called.
        void run();

        // Returns the time elapsed (in seconds) since the last frame.
        float getDeltaTime() const;

        // Signals the engine to stop running after the current frame.
        void exit();

    private:
        bool running{ false }; // True while the main loop is active.
        float deltaTime{ 0.0f }; // Time elapsed since last frame (seconds).
        std::string startMap; // Name of the map to load at startup.
        std::unique_ptr<EngineContext> context; // Holds subsystem managers and game state.
    };
}

