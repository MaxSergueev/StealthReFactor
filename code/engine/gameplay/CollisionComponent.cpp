#include "CollisionComponent.hpp"
#include "Entity.hpp"
#include <engine/physics/PhysicsManager.hpp>
#include "TransformComponent.hpp"

namespace engine {
    namespace gameplay {

        CollisionComponent::CollisionComponent(physics::Manager& physicsManager,
            float sizeX, float sizeY, float sizeZ)
            : _physicsManager(physicsManager)
        {
            _geometryId = dCreateBox(_physicsManager.getSpaceId(),
                sizeX, sizeY, sizeZ);
            if (_geometryId)
            {
                dGeomSetData(_geometryId, getOwner());
            }
        }

        CollisionComponent::~CollisionComponent()
        {
            if (_geometryId)
            {
                dGeomDestroy(_geometryId);
                _geometryId = nullptr;
            }
        }

        void CollisionComponent::update()
        {
            if (auto* transform = getOwner()->getComponent<TransformComponent>())
            {
                const auto& position = transform->getPosition();
                setGeometryPosition(position);
            }

            checkCollisions();
        }

        void CollisionComponent::setGeometryPosition(const sf::Vector2f& position)
        {
            if (_geometryId)
            {
                dGeomSetPosition(_geometryId, position.x, position.y, 0.0);
            }
        }

        void CollisionComponent::checkCollisions()
        {
            if (!_onCollision || !_geometryId) return;

            auto collisions = _physicsManager.getCollisionsWith(_geometryId);
            for (auto& geomId : collisions)
            {
                if (auto* entity = reinterpret_cast<Entity*>(dGeomGetData(geomId)))
                {
                    _onCollision(entity);
                }
            }
        }
    }
}

