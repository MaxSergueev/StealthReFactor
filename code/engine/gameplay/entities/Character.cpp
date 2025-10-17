#include "Character.hpp"
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/GameplayManager.hpp>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            Character::Character(graphics::Manager& graphicsManager,
                physics::Manager& physicsManager)
                : _graphicsManager(graphicsManager)
            {
                addComponent(std::make_unique<TransformComponent>());
                transform = getComponent<TransformComponent>();

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

            void Character::update()
            {
                Entity::update();
            }

            void Character::draw()
            {
                if (transform)
                {
                    _graphicsManager.draw(shapeList, transform->getTransform());
                }
            }

            const sf::Transform& Character::getTransform() const
            {
                return transform ? transform->getTransform() : sf::Transform::Identity;
            }
        }
    }
}




