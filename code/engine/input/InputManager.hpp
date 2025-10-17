#pragma once

#include <set>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace engine
{
    namespace graphics { class Manager; }

    namespace input
    {
        class Manager
        {
        public:
            Manager() = default;
            ~Manager() = default;

            bool isKeyPressed(sf::Keyboard::Key key) const;
            bool isKeyJustPressed(sf::Keyboard::Key key) const;
            bool isKeyJustReleased(sf::Keyboard::Key key) const;

            void clear();

            void onKeyPressed(const sf::Event::KeyEvent& event);

            void onKeyReleased(const sf::Event::KeyEvent& event);

            void setGraphicsManager(graphics::Manager* gfxMgr) { _graphicsManager = gfxMgr; }

        private:
            std::set<sf::Keyboard::Key> justPressedKeys;

            std::set<sf::Keyboard::Key> justReleasedKeys;

            // Non-owning pointer to graphics manager for focus checks.
            graphics::Manager* _graphicsManager{ nullptr };
        };
    }
}


