#pragma once
#include <memory>
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/graphics/GraphicsManager.hpp"
#include "engine/physics/PhysicsManager.hpp"
#include "engine/input/InputManager.hpp"

namespace engine {
    class EngineContext {
    public:
        EngineContext() {
            graphicsManager = std::make_unique<graphics::Manager>();
            inputManager = std::make_unique<input::Manager>();
            physicsManager = std::make_unique<physics::Manager>();
            gameplayManager = std::make_unique<gameplay::Manager>();

            // Establish cross-references between managers for event and state sharing.
            graphicsManager->setInputManager(inputManager.get());
            inputManager->setGraphicsManager(graphicsManager.get());
            gameplayManager->setGraphicsManager(graphicsManager.get());
            gameplayManager->setPhysicsManager(physicsManager.get());
            gameplayManager->setInputManager(inputManager.get());

            // Sync graphics view center with gameplay manager's view center when requested.
            graphicsManager->onViewCenterRequested.addCallback([this](const sf::Vector2f&) {
                if (gameplayManager && graphicsManager) {
                    graphicsManager->setViewCenter(gameplayManager->getViewCenter());
                }
                });
        }

        // Returns a raw pointer to the gameplay manager.
        gameplay::Manager* getGameplayManager() const { return gameplayManager.get(); }

        // Subsystem managers owned by the context.
        std::unique_ptr<graphics::Manager> graphicsManager;   // Handles rendering and window events.
        std::unique_ptr<physics::Manager> physicsManager;     // Handles physics simulation and collisions.
        std::unique_ptr<input::Manager> inputManager;         // Handles input state and events.
        std::unique_ptr<gameplay::Manager> gameplayManager;   // Handles game state, entities, and map logic.
    };
}
