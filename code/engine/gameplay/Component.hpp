#pragma once
namespace engine
{
    namespace gameplay
    {
        class Entity;

        // Base class for all components that can be attached to an Entity.
        class Component
        {
        public:
            virtual ~Component() = default;
            virtual void update() {}
            virtual void draw() {}

            // Sets the owning entity for this component.
            void setOwner(Entity* entity) { _owner = entity; }

            // Returns the owning entity, or nullptr if not set.
            Entity* getOwner() const { return _owner; }

        private:
            Entity* _owner{ nullptr }; // Pointer to the entity that owns this component.
        };
    }
}