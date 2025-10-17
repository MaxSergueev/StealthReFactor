#pragma once
#include <ode/collision.h>
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <functional>

namespace engine {
    namespace physics { class Manager; }

    namespace gameplay {
        // Handles collision detection for an entity using ODE.
        class CollisionComponent : public Component {
        public:
            // Callback type for collision events.
            using CollisionCallback = std::function<void(Entity*)>;

            // Registers a collision geometry with the physics manager.
            CollisionComponent(physics::Manager& physicsManager,
                float sizeX, float sizeY, float sizeZ = 1.0f);
            virtual ~CollisionComponent();

            virtual void update() override;

            // Sets the position of the collision geometry in the physics world.
            void setGeometryPosition(const sf::Vector2f& position);

            // Returns the ODE geometry ID for this component.
            dGeomID getGeometryId() const { return _geometryId; }

            // Sets the callback to be invoked when a collision occurs.
            void setOnCollision(CollisionCallback callback) { _onCollision = callback; }

            // Checks for collisions and invokes the callback if set.
            void checkCollisions();

        private:
            physics::Manager& _physicsManager; // Reference to the physics manager.
            dGeomID _geometryId{ nullptr };    // ODE geometry ID for collision detection.
            CollisionCallback _onCollision;    // Callback for collision events.
        };
    }
}




