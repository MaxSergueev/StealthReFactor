#pragma once

#include <set>
#include <vector>
#include <ode/collision.h>

namespace engine
{
    namespace physics
    {
        class Manager
        {
        public:
            // Represents a collision between two ODE geometry objects.
            struct Collision
            {
                dGeomID o1; // First geometry object involved in the collision.
                dGeomID o2; // Second geometry object involved in the collision.

                Collision(dGeomID o1, dGeomID o2);
            };

            // Container for all collisions detected in the current frame.
            using Collisions = std::vector<Collision>;

            Manager();
            ~Manager();

            void update();

            // Returns the ODE space ID managed by this instance.
            dSpaceID getSpaceId() const;

            // Returns a set of geometry objects that collided with the specified object in the current frame.
            std::set<dGeomID> getCollisionsWith(dGeomID object) const;

        private:
            dSpaceID _spaceId; // ODE space for collision detection.
            Collisions _frameCollisions; // Collisions detected in the current frame.

            // ODE callback for registering collisions during simulation.
            static void nearCallback(void* data, dGeomID o1, dGeomID o2);
        };
    }
}

