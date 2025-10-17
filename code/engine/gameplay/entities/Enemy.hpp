#pragma once

#include <string>
#include <engine/gameplay/entities/Character.hpp>
#include <engine/gameplay/Observer.hpp>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            class Enemy : public Character
            {
            public:
                // Loads archetype data and sets up components.
                Enemy(graphics::Manager& graphicsManager,
                    physics::Manager& physicsManager,
                    const std::string& archetypeName);
                virtual void update() override;

                Observer<> onPlayerSpotted; // Notifies when the player is detected.

                // Call this when the player moves to update tracking and vision.
                void onPlayerMoved(const sf::Vector2f& playerPosition);

            private:
                float visionRadius{ 0 };           // Detection radius for player.
                int shootDelay{ 0 };               // Delay before shooting after spotting player.
                int shootDelayCounter{ 0 };        // Tracks frames since player was spotted.
                sf::Vector2f lastKnownPlayerPosition; // Used for vision and tracking.

                void loadArchetype(const std::string& archetypeName);

                // Checks if the player is within vision and triggers events.
                void checkPlayerSpotted();
            };
        }
    }
}
