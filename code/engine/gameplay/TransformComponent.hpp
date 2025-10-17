#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

namespace engine
{
    namespace gameplay
    {
        // Handles position, rotation, and transformation matrix for an entity.
        class TransformComponent : public Component
        {
        public:
            TransformComponent();

            const sf::Vector2f& getPosition() const;
            void setPosition(const sf::Vector2f& newPosition);

            float getRotation() const;
            void setRotation(float newRotation);

            // Returns the transformation matrix representing position and rotation.
            const sf::Transform& getTransform() const;

        private:
            sf::Vector2f _position{};   // World position of the entity.
            float _rotation{ 0.f };     // Rotation in degrees.
            sf::Transform _transform;   // Cached transformation matrix.

            // Updates the transformation matrix after position or rotation changes.
            void updateTransform();
        };
    }
}


