#include "Application.hpp"

namespace igpp::c02_01
{

Application::Application() : window_(sf::VideoMode(960, 540), "02_Command_01_Configure_Input_and_Actors")
{
    window_.setFramerateLimit(60);
    textures_.load(TextureId::DWARF, "assets/dwarf.png");

    dwarf_.setTexture(textures_.get(TextureId::DWARF));
    dwarf_.setTextureRect({0, 0, 64, 32});
    dwarf_.setPosition(480, 170);
    dwarf_.setScale(5, 5);
}

void Application::run()
{
    sf::Clock deltaTimer;
    while (window_.isOpen())
    {
        processEvents();
        update(deltaTimer.restart());
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

void Application::update(const sf::Time& deltaTime)
{
}

void Application::render()
{
    window_.clear();

    window_.draw(dwarf_);

    window_.display();
}

} // namespace igpp::c02_01
