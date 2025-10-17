#pragma once

#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/TransformComponent.hpp>
#include <engine/gameplay/CollisionComponent.hpp>

namespace engine
{
    namespace graphics { class Manager; }
    namespace physics { class Manager; }

    namespace gameplay
    {
        namespace entities
        {
            class Target : public Entity
            {
            public:
                // Requires graphics and physics managers for component setup.
                Target(graphics::Manager& graphicsManager,
                    physics::Manager& physicsManager);

                virtual void update() override;
                virtual void draw() override;

                // Returns the current transform, or identity if not available.
                const sf::Transform& getTransform() const;

                // Returns the current position, or (0,0) if not available.
                const sf::Vector2f& getPosition() const;

            private:
                graphics::Manager& _graphicsManager; // Used for rendering.
                graphics::ShapeList shapeList;       // Stores drawable shapes for this target.
                TransformComponent* transform{ nullptr }; // Cached pointer for convenience.
                CollisionComponent* collision{ nullptr }; // Cached pointer for convenience.
            };
        }
    }
}


