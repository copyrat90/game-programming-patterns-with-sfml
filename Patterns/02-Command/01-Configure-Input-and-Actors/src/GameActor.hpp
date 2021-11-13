#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

namespace igpp::c02_01
{

class GameActor : public sf::Drawable, public sf::Transformable
{
public:
    virtual ~GameActor() = default;

    virtual void update(const sf::Time& dt) = 0;
    virtual void jump() = 0;
};

} // namespace igpp::c02_01
