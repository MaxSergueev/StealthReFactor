#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <SFML/System/Vector2.hpp>
#include "Component.hpp"

namespace engine
{
    namespace gameplay
    {
        class TransformComponent;

        class Entity
        {
        public:
            virtual ~Entity() = default;

            // Adds or replaces a component of type T.
            // The component's owner is set to this entity.
            template<typename T>
            void addComponent(std::unique_ptr<T> component);

            // Returns a pointer to the component of type T, or nullptr if not present.
            template<typename T>
            T* getComponent() const;

            // Returns true if a component of type T is attached.
            template<typename T>
            bool hasComponent() const;

            virtual void update();
            virtual void draw();

            // These methods delegate to TransformComponent if present.
            virtual void setPosition(const sf::Vector2f& position);
            virtual const sf::Vector2f& getPosition() const;
            virtual void setRotation(float rotation);
            virtual float getRotation() const;

        private:
            // Stores components by their type for fast lookup and replacement.
            std::unordered_map<std::type_index, std::unique_ptr<Component>> _components;
        };

        template<typename T>
        void Entity::addComponent(std::unique_ptr<T> component)
        {
            static_assert(std::is_base_of<Component, T>::value,
                "T must inherit from Component");
            component->setOwner(this);
            _components[std::type_index(typeid(T))] = std::move(component);
        }

        template<typename T>
        T* Entity::getComponent() const
        {
            auto it = _components.find(std::type_index(typeid(T)));
            return it != _components.end() ?
                static_cast<T*>(it->second.get()) : nullptr;
        }

        template<typename T>
        bool Entity::hasComponent() const
        {
            return _components.find(std::type_index(typeid(T))) !=
                _components.end();
        }
    }
}

