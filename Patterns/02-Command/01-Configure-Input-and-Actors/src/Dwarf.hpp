#pragma once

#include "GameActor.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "AssetManagers.hpp"

namespace igpp::c02_01
{

class Dwarf : public GameActor
{
public:
    enum AnimationState
    {
        IDLE,
        JUMP,
        WEAK_ATTACK,
        STRONG_ATTACK,
        SPECIAL_ATTACK,
        TOTAL_COUNT_
    };

public:
    Dwarf(TextureManager&);

    void update(const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void nextFrame();

    void jump() override;
    void weakAttack() override;
    void strongAttack() override;
    void specialAttack() override;

private:
    // Change the animation and reset frame & time to 0
    void changeAnimation(AnimationState);

private:
    sf::Sprite sprite_;
    AnimationState animationState_;
    sf::Time animationTimer_;
    int animationFrame_ = 0;
    int animationLoopCount_ = 0;
};

} // namespace igpp::c02_01
