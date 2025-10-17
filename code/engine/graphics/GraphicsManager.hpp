#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/gameplay/Observer.hpp>
#include <SFML/System/Vector2.hpp>

namespace engine
{
    class Engine;
    namespace input { class Manager; }

    namespace graphics
    {
        class ShapeList;

        class Manager
        {
        public:
            Manager();
            ~Manager();

            void update(Engine& engine);

            void clear();

            void draw(const ShapeList& shapeList, const sf::Transform& transform);

            // Displays the contents of the window.
            void display();

            // Returns true if the window currently has focus.
            bool hasFocus() const;

            // Sets the input manager used for event handling.
            void setInputManager(input::Manager* inMgr) { inputManager = inMgr; }

            gameplay::Observer<> onWindowClosed;
            gameplay::Observer<> onFocusChanged;
            gameplay::Observer<sf::Vector2f> onViewCenterRequested;

            // Sets the center of the window's view.
            void setViewCenter(const sf::Vector2f& center);

        private:
            sf::RenderWindow window;

            static const sf::Int16 WINDOW_WIDTH = 800;
            static const sf::Int16 WINDOW_HEIGHT = 600;

            // Non-owning pointer to the input manager.
            input::Manager* inputManager{ nullptr };
        };
    }
}


