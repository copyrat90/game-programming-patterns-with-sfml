#pragma once

#include "GameActor.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "AssetManagers.hpp"

namespace igpp::c02_01
{

class Dwarf : public GameActor
{
public:
    enum class AnimationState
    {
        IDLE,
        JUMP,
        WEAK_ATTACK,
        STRONG_ATTACK,
        SPECIAL_ATTACK
    };

public:
    Dwarf(TextureManager&);

    void update(const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void jump() override;
    void weakAttack() override;
    void strongAttack() override;
    void specialAttack() override;

private:
    sf::Sprite sprite_;
    AnimationState animationState_;
};

} // namespace igpp::c02_01
