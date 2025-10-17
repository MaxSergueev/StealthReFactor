#pragma once

#include <set>
#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "GameplayConstants.hpp"
#include "Observer.hpp"

namespace engine
{
    namespace graphics { class Manager; }
    namespace physics { class Manager; }
    namespace input { class Manager; }

    namespace gameplay
    {
        class Entity;

        namespace entities
        {
            class Player;
        }

        // Manages game state, entities, and map transitions.
        class Manager
        {
        public:
            Manager();
            ~Manager();

            // Event observers for map and entity lifecycle.
            Observer<const std::string&> onMapLoad;
            Observer<const std::string&> onMapComplete;
            Observer<> onGameOver;
            Observer<Entity*> onEntitySpawned;
            Observer<Entity*> onEntityDestroyed;

            void update();
            void draw();
            void gameOver();
            sf::Vector2f getViewCenter() const;
            void loadMap(const std::string& mapName);
            void loadNextMap();
            const entities::Player& getPlayer() const;

            // Setters for external managers. These are non-owning pointers.
            void setGraphicsManager(graphics::Manager* gfxMgr) { _graphicsManager = gfxMgr; }
            void setPhysicsManager(physics::Manager* physMgr) { _physicsManager = physMgr; }
            void setInputManager(input::Manager* inMgr) { _inputManager = inMgr; }

        private:
            std::set<std::unique_ptr<Entity>> _entities; // All active entities in the game.
            entities::Player* _playerEntity{ nullptr };  // Cached pointer to the player entity.

            // Non-owning pointers to subsystem managers.
            graphics::Manager* _graphicsManager{ nullptr };
            physics::Manager* _physicsManager{ nullptr };
            input::Manager* _inputManager{ nullptr };

            std::string _currentMapName; // Name of the currently loaded map.
            std::string _nextMapName;    // Name of the next map to load.
            int _rows{ 0 };              // Map row count.
            int _columns{ 0 };           // Map column count.
            bool _preventMapCompletion{ false }; // Used to block map completion until ready.
            bool _nextMapRequested{ false };     // Indicates if a map transition is pending.
        };
    }
}


