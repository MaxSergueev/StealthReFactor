#include "Target.hpp"
#include <memory>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            Target::Target(graphics::Manager& graphicsManager,
                physics::Manager& physicsManager)
                : _graphicsManager(graphicsManager)
            {
                addComponent(std::make_unique<TransformComponent>());
                transform = getComponent<TransformComponent>();

                shapeList.load("target");

                auto collisionComp = std::make_unique<CollisionComponent>(
                    physicsManager,
                    CELL_SIZE * 0.9f,
                    CELL_SIZE * 0.9f);

                addComponent(std::move(collisionComp));
                collision = getComponent<CollisionComponent>();

                if (collision && collision->getGeometryId())
                {
                    dGeomSetData(collision->getGeometryId(), this);
                }
            }

            void Target::update()
            {
                Entity::update();
            }

            void Target::draw()
            {
                if (transform)
                {
                    _graphicsManager.draw(shapeList, transform->getTransform());
                }
            }

            const sf::Transform& Target::getTransform() const
            {
                return transform ? transform->getTransform() : sf::Transform::Identity;
            }

            const sf::Vector2f& Target::getPosition() const
            {
                static const sf::Vector2f DEFAULT_POSITION(0.0f, 0.0f);
                return transform ? transform->getPosition() : DEFAULT_POSITION;
            }
        }
    }
}


