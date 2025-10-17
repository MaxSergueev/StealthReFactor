#include "TransformComponent.hpp"

namespace engine
{
    namespace gameplay
    {
        TransformComponent::TransformComponent()
            : _position(0.f, 0.f)
            , _rotation(0.f)
        {
            updateTransform();
        }

        const sf::Vector2f& TransformComponent::getPosition() const
        {
            return _position;
        }

        void TransformComponent::setPosition(const sf::Vector2f& newPosition)
        {
            _position = newPosition;
            updateTransform();
        }

        float TransformComponent::getRotation() const
        {
            return _rotation;
        }

        void TransformComponent::setRotation(float newRotation)
        {
            _rotation = newRotation;
            updateTransform();
        }

        const sf::Transform& TransformComponent::getTransform() const
        {
            return _transform;
        }

        void TransformComponent::updateTransform()
        {
            _transform = sf::Transform::Identity;
            _transform.translate(_position);
            _transform.rotate(_rotation);
        }
    }
}

