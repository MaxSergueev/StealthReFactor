#include "engine/gameplay/GameplayManager.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/Engine.hpp>
#include <engine/gameplay/entities/Enemy.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>
#include "engine/gameplay/TransformComponent.hpp"

namespace engine
{
    namespace gameplay
    {
        Manager::Manager()
        {
            if (_graphicsManager)
            {
                _graphicsManager->onWindowClosed.addCallback([this]() {
                    });

                _graphicsManager->onFocusChanged.addCallback([this]() {
                    });

                _graphicsManager->onViewCenterRequested.addCallback([this](const sf::Vector2f&) {
                    if (_graphicsManager)
                    {
                        _graphicsManager->setViewCenter(this->getViewCenter());
                    }
                    });
            }
        }

        Manager::~Manager() = default;

        void Manager::update()
        {
            if (!_physicsManager || !_inputManager) return;

            for (const auto& entity : _entities)
            {
                entity->update();
            }

            _preventMapCompletion = false;
            if (_nextMapRequested && !_nextMapName.empty())
            {
                _nextMapRequested = false;
                loadMap(_nextMapName);
            }
        }

        void Manager::draw()
        {
            if (!_graphicsManager) return;

            for (const auto& entity : _entities)
            {
                entity->draw();
            }
        }

        void Manager::gameOver()
        {
            std::cout << "Game over" << std::endl;
            onGameOver.notify();
            loadMap(_currentMapName);
        }

        sf::Vector2f Manager::getViewCenter() const
        {
            return sf::Vector2f{ _columns * (CELL_SIZE / 2.f), _rows * (CELL_SIZE / 2.f) };
        }

        void Manager::loadMap(const std::string& mapName)
        {
            if (!_graphicsManager || !_physicsManager || !_inputManager) return;

            for (const auto& entity : _entities)
            {
                onEntityDestroyed.notify(entity.get());
            }
            _entities.clear();
            _playerEntity = nullptr;

            std::stringstream filename;
            filename << "maps/" << mapName << ".xml";

            pugi::xml_document doc;
            pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

            if (result)
            {
                assert(!doc.empty());
                auto xmlMap = doc.first_child();

                _rows = std::stoi(xmlMap.child_value("rows"));
                assert(_rows >= 0);

                _columns = std::stoi(xmlMap.child_value("columns"));
                assert(_columns >= 0);

                for (auto& xmlElement : xmlMap.child("elements").children())
                {
                    std::unique_ptr<Entity> entity;

                    if (!std::strcmp(xmlElement.name(), "enemy"))
                    {
                        int row = std::stoi(xmlElement.child_value("row"));
                        assert(row >= 0 && row < _rows);

                        int column = std::stoi(xmlElement.child_value("column"));
                        assert(column >= 0 && column < _columns);

                        std::string archetypeName = xmlElement.child_value("archetype");

                        auto enemy = std::make_unique<entities::Enemy>(*_graphicsManager, *_physicsManager, archetypeName);
                        enemy->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

                        enemy->onPlayerSpotted.addCallback([this]() {
                            this->gameOver();
                            });

                        if (_playerEntity)
                        {
                            _playerEntity->onPositionChanged.addCallback([enemyPtr = enemy.get()](const sf::Vector2f& pos) {
                                enemyPtr->onPlayerMoved(pos);
                                });
                        }

                        entity = std::move(enemy);
                    }

                    if (!std::strcmp(xmlElement.name(), "player"))
                    {
                        int row = std::stoi(xmlElement.child_value("row"));
                        assert(row >= 0 && row < _rows);

                        int column = std::stoi(xmlElement.child_value("column"));
                        assert(column >= 0 && column < _columns);

                        auto player = std::make_unique<entities::Player>(*_graphicsManager, *_physicsManager, *_inputManager);
                        player->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

                        player->onTargetCollision.addCallback([this]() {
                            this->loadNextMap();
                            });

                        _playerEntity = player.get();

                        for (const auto& existingEntity : _entities)
                        {
                            if (auto* enemy = dynamic_cast<entities::Enemy*>(existingEntity.get()))
                            {
                                player->onPositionChanged.addCallback([enemy](const sf::Vector2f& pos) {
                                    enemy->onPlayerMoved(pos);
                                    });
                            }
                        }

                        entity = std::move(player);
                    }

                    if (!std::strcmp(xmlElement.name(), "target"))
                    {
                        int row = std::stoi(xmlElement.child_value("row"));
                        assert(row >= 0 && row < _rows);

                        int column = std::stoi(xmlElement.child_value("column"));
                        assert(column >= 0 && column < _columns);

                        entity = std::make_unique<entities::Target>(*_graphicsManager, *_physicsManager);
                        entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });
                    }

                    if (entity)
                    {
                        Entity* entityPtr = entity.get();
                        _entities.insert(std::move(entity));
                        onEntitySpawned.notify(entityPtr);
                    }
                }

                _currentMapName = mapName;
                _nextMapName = xmlMap.child_value("next_map");
                _preventMapCompletion = true;

                onMapLoad.notify(mapName);
            }
            else
            {
                std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
                std::cerr << "Error description: " << result.description() << std::endl;
                std::cerr << "Error offset: " << result.offset << std::endl;
            }
        }

        void Manager::loadNextMap()
        {
            if (!_preventMapCompletion)
            {
                onMapComplete.notify(_nextMapName);
                _nextMapRequested = true;
            }
        }

        const entities::Player& Manager::getPlayer() const
        {
            assert(_playerEntity);
            return *_playerEntity;
        }
    }
}
