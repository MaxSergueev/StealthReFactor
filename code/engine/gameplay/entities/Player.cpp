#include "engine/gameplay/entities/Player.hpp"
#include  "engine/gameplay/GameplayConstants.hpp"
#include <engine/gameplay/entities/Target.hpp>
#include <engine/Engine.hpp>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            Player::Player(graphics::Manager& graphicsManager,
                physics::Manager& physicsManager,
                input::Manager& inputManager)
                : Character(graphicsManager, physicsManager)
                , _inputManager(inputManager)
            {
                shapeList.load("player");
                transform = getComponent<TransformComponent>();
                collision = getComponent<CollisionComponent>();

                if (collision)
                {
                    collision->setOnCollision([this](Entity* other) {
                        if (auto* target = dynamic_cast<Target*>(other))
                        {
                            onTargetCollision.notify();
                        }
                        });
                }
            }

            void Player::update()
            {
                justMoved = false;
                if (!transform) return;

                sf::Vector2f newPosition = transform->getPosition();
                float newRotation = transform->getRotation();

                if (_inputManager.isKeyJustPressed(sf::Keyboard::Left))
                {
                    justMoved = true;
                    newPosition.x -= CELL_SIZE;
                    newRotation = 180.f;
                }
                else if (_inputManager.isKeyJustPressed(sf::Keyboard::Right))
                {
                    justMoved = true;
                    newPosition.x += CELL_SIZE;
                    newRotation = 0.f;
                }
                else if (_inputManager.isKeyJustPressed(sf::Keyboard::Up))
                {
                    justMoved = true;
                    newPosition.y -= CELL_SIZE;
                    newRotation = -90.f;
                }
                else if (_inputManager.isKeyJustPressed(sf::Keyboard::Down))
                {
                    justMoved = true;
                    newPosition.y += CELL_SIZE;
                    newRotation = 90.f;
                }

                if (justMoved)
                {
                    transform->setPosition(newPosition);
                    transform->setRotation(newRotation);
                    onPositionChanged.notify(newPosition);
                }

                Character::update();
            }

            bool Player::hasJustMoved() const
            {
                return justMoved;
            }
        }
    }
}


