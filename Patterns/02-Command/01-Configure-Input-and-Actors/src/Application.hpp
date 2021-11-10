#pragma once

#include <SFML/Graphics.hpp>

#include "AssetManagers.hpp"

namespace igpp::c02_01
{

class Application
{
public:
    Application();
    void run();

private:
    void processEvents();
    void update(const sf::Time& deltaTime);
    void render();

private:
    sf::RenderWindow window_;
    TextureManager textures_;

    sf::Sprite dwarf_;
};

} // namespace igpp::c02_01
