#include "Enemy.hpp"
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/gameplay/TransformComponent.hpp>
#include <engine/gameplay/GameplayConstants.hpp> 

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
            Enemy::Enemy(graphics::Manager& graphicsManager,
                physics::Manager& physicsManager,
                const std::string& archetypeName)
                : Character(graphicsManager, physicsManager)
            {
                addComponent(std::make_unique<TransformComponent>());
                transform = getComponent<TransformComponent>();

                loadArchetype(archetypeName);
            }

            void Enemy::update()
            {
                checkPlayerSpotted();
            }

            void Enemy::checkPlayerSpotted()
            {
                if (!transform) return;

                const auto& myPosition = transform->getPosition();
                auto offset = lastKnownPlayerPosition - myPosition;
                offset /= CELL_SIZE;
                float distance2 = offset.x * offset.x + offset.y * offset.y;

                // Only check vision if within radius
                if (distance2 <= visionRadius * visionRadius)
                {
                    // Calculate angle between enemy's facing direction and player
                    float enemyAngle = transform->getRotation() * (3.14159f / 180.f);
                    float toPlayerAngle = std::atan2(offset.y, offset.x);

                    // Normalize angles
                    while (enemyAngle < 0) enemyAngle += 2 * 3.14159f;
                    while (toPlayerAngle < 0) toPlayerAngle += 2 * 3.14159f;

                    // Calculate angle difference
                    float angleDiff = std::abs(enemyAngle - toPlayerAngle);
                    while (angleDiff > 3.14159f) angleDiff = 2 * 3.14159f - angleDiff;

                    // Check if player is in front
					if (angleDiff < 3.14159f / 2.f)  // Vision cone of 90 degrees
                    {
                        if (shootDelayCounter < shootDelay)
                        {
                            ++shootDelayCounter;
                        }
                        else
                        {
                            onPlayerSpotted.notify();
                        }
                    }
                }
                else
                {
                    shootDelayCounter = 0;
                }
            }

            void Enemy::onPlayerMoved(const sf::Vector2f& playerPosition)
            {
                lastKnownPlayerPosition = playerPosition;
                checkPlayerSpotted();
            }

			void Enemy::loadArchetype(const std::string &archetypeName)
			{
				std::stringstream filename;
				filename << "archetypes/" << archetypeName << ".xml";

				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

				if (result)
				{
					assert(!doc.empty());
					auto xmlArchetype = doc.first_child();

					std::string shapeListName = xmlArchetype.child_value("shapelist");
					assert(shapeList.load(shapeListName));

					visionRadius = std::stof(xmlArchetype.child_value("vision_radius"));
					assert(visionRadius > 0.f);

					shootDelay = std::stoi(xmlArchetype.child_value("shoot_delay"));
					assert(shootDelay >= 0);
				}
				else
				{
					std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
					std::cerr << "Error description: " << result.description() << std::endl;
					std::cerr << "Error offset: " << result.offset << std::endl;
				}
			}
		}
	}
}
