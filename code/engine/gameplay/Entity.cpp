#include "Entity.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

namespace engine
{
    namespace gameplay
    {
        void Entity::update()
        {
            for (auto& pair : _components)
            {
                if (pair.second)
                    pair.second->update();
            }
        }

        void Entity::draw()
        {
            for (auto& pair : _components)
            {
                if (pair.second)
                    pair.second->draw();
            }
        }

        void Entity::setPosition(const sf::Vector2f& position)
        {
            if (auto* transform = getComponent<TransformComponent>())
                transform->setPosition(position);
        }

        const sf::Vector2f& Entity::getPosition() const
        {
            static const sf::Vector2f DEFAULT_POSITION(0.0f, 0.0f);
            auto* transform = getComponent<TransformComponent>();
            return transform ? transform->getPosition() : DEFAULT_POSITION;
        }

        void Entity::setRotation(float rotation)
        {
            if (auto* transform = getComponent<TransformComponent>())
                transform->setRotation(rotation);
        }

        float Entity::getRotation() const
        {
            auto* transform = getComponent<TransformComponent>();
            return transform ? transform->getRotation() : 0.0f;
        }
    }
}
