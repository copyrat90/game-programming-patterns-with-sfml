#include "Dwarf.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace igpp::c02_01
{

Dwarf::Dwarf(TextureManager& textures)
{
    sprite_.setTexture(textures.get(TextureId::DWARF));
    sprite_.setTextureRect({0, 0, 64, 32});
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2, bounds.height / 2);

    // setPosition(600, 250);
    setPosition(480, 270);
    setScale(5, 5);
}

void Dwarf::jump()
{
    // TODO: Set the animationState_ to jumping
    // TODO: Restart the animation timer
}

void Dwarf::update(const sf::Time& dt)
{
    // TODO: Update the animation with dt and timer
}

void Dwarf::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}

} // namespace igpp::c02_01
