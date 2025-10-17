#include "engine/graphics/GraphicsManager.hpp"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/Engine.hpp>

namespace engine
{
    namespace graphics
    {
        Manager::Manager()
        {
            window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");
            window.setVerticalSyncEnabled(true);
            sf::View view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
            window.setView(view);
        }

        Manager::~Manager()
        {
            window.close();
        }

        void Manager::update(Engine& engine)
        {
            if (!inputManager) return;

            inputManager->clear();

            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    onWindowClosed.notify();
                    engine.exit();
                    break;

                case sf::Event::KeyPressed:
                    inputManager->onKeyPressed(event.key);
                    break;

                case sf::Event::KeyReleased:
                    inputManager->onKeyReleased(event.key);
                    break;

                case sf::Event::GainedFocus:
                case sf::Event::LostFocus:
                    onFocusChanged.notify();
                    break;

                default:
                    break;
                }
            }
        }

        void Manager::clear()
        {
            window.clear(sf::Color::Black);
            onViewCenterRequested.notify(window.getView().getCenter());
        }

        void Manager::setViewCenter(const sf::Vector2f& center)
        {
            sf::View view{ center, sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
            window.setView(view);
        }

        void Manager::draw(const ShapeList& shapeList, const sf::Transform& transform)
        {
            sf::RenderStates renderStates{ transform };
            for (auto shape : shapeList.getShapes())
            {
                window.draw(*shape, renderStates);
            }
        }

        void Manager::display()
        {
            window.display();
        }

        bool Manager::hasFocus() const
        {
            return window.hasFocus();
        }
    }
}
