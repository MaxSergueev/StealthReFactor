#pragma once

#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/TransformComponent.hpp>
#include <engine/gameplay/CollisionComponent.hpp>

namespace engine
{
    namespace graphics { class Manager; }

    namespace gameplay
    {
        namespace entities
        {
            class Character : public Entity
            {
            public:
                // Requires graphics and physics managers for component setup.
                Character(graphics::Manager& graphicsManager,
                    physics::Manager& physicsManager);
                virtual ~Character() = default;

                virtual void draw() override;
                virtual void update() override;

                // Returns the current transform, or identity if not available.
                const sf::Transform& getTransform() const;

            protected:
                graphics::Manager& _graphicsManager; // Used for rendering.
                graphics::ShapeList shapeList;       // Stores drawable shapes for this character.
                bool isWalking{ false };             // Indicates if the character is currently moving.
                TransformComponent* transform{ nullptr }; // Cached pointer for convenience.
                CollisionComponent* collision{ nullptr }; // Cached pointer for convenience.
            };
        }
    }
}
