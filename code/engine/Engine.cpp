#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>

namespace engine
{
    Engine::Engine() : context(std::make_unique<EngineContext>())
    {
        context->gameplayManager->onGameOver.addCallback([this]() {
            });
    }

    void Engine::loadConfiguration()
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("configuration.xml");

        if (result)
        {
            assert(!doc.empty());
            auto configuration = doc.first_child();
            startMap = configuration.child_value("start_map");
        }
        else
        {
            std::cerr << "Configuration parsed with errors." << std::endl;
            std::cerr << "Error description: " << result.description() << std::endl;
            std::cerr << "Error offset: " << result.offset << std::endl;
        }
    }

    void Engine::run()
    {
        running = true;

        context->gameplayManager->loadMap(startMap);

        sf::Clock clock;
        while (running)
        {
            deltaTime = clock.restart().asSeconds();

            context->physicsManager->update();
            context->gameplayManager->update();
            context->graphicsManager->update(*this);

            context->graphicsManager->clear();

            context->gameplayManager->draw();

            context->graphicsManager->display();
        }
    }

    float Engine::getDeltaTime() const
    {
        return deltaTime;
    }

    void Engine::exit()
    {
        running = false;
    }
}


