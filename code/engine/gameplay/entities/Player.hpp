#pragma once
#include <engine/gameplay/entities/Character.hpp>
#include <engine/gameplay/TransformComponent.hpp>
#include <engine/gameplay/Observer.hpp>

namespace engine
{
    namespace input { class Manager; }

    namespace gameplay
    {
        namespace entities
        {
            class Player : public Character
            {
            public:
                // Requires all three managers due to Character base class and direct input usage.
                Player(graphics::Manager& graphicsManager,
                    physics::Manager& physicsManager,
                    input::Manager& inputManager);

                virtual void update() override;

                // Returns true if the player moved this frame.
                bool hasJustMoved() const;

                Observer<> onTargetCollision; // Notifies when player collides with a target.
                Observer<const sf::Vector2f&> onPositionChanged; // Notifies when position changes.

            private:
                input::Manager& _inputManager; // Used for handling player input.
                bool justMoved{ false };       // Tracks if the player moved this frame.
            };
        }
    }
}
