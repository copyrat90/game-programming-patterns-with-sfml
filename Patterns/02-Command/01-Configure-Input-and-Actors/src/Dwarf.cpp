#include "Dwarf.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "global.hpp"

namespace igpp::c02_01
{

namespace
{
const sf::Time ANIMATION_FRAME_TIME = sf::seconds(0.15f);
constexpr int NUMBER_OF_FRAMES[Dwarf::AnimationState::TOTAL_COUNT_] = {5, 5, 6, 7, 2};
constexpr int SPRITE_Y_INDEX[Dwarf::AnimationState::TOTAL_COUNT_] = {0, 5, 3, 2, 4};
// -1: infinite
constexpr int LOOP_AMOUNT[Dwarf::AnimationState::TOTAL_COUNT_] = {-1, 1, 1, 1, 3};
constexpr int SPRITE_WIDTH = 64;
constexpr int SPRITE_HEIGHT = 32;

const std::string ANIM_STATE_STRS[Dwarf::AnimationState::TOTAL_COUNT_] = {"Idle", "Jump", "Weak Attack",
                                                                          "Strong Attack", "Special Attack"};
} // namespace

Dwarf::Dwarf(TextureManager& textures, FontManager& fonts) : animationState_(AnimationState::IDLE)
{
    sprite_.setTexture(textures.get(TextureId::DWARF));
    sprite_.setTextureRect({0, 0, SPRITE_WIDTH, SPRITE_HEIGHT});
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2, bounds.height / 2);
    sprite_.setScale(5, 5);

    animationStateText_.setFont(fonts.get(FontId::D2CODING));
    animationStateText_.setCharacterSize(25);
    animationStateText_.setFillColor(sf::Color::White);
    animationStateText_.setPosition(0, 100);

    setPosition(600, 250);

    changeAnimation(animationState_);
}

void Dwarf::update(const sf::Time& dt)
{
    // Update the animation with dt and timer
    animationTimer_ += dt;
    if (animationTimer_ >= ANIMATION_FRAME_TIME)
    {
        animationTimer_ -= ANIMATION_FRAME_TIME;
        nextFrame();
    }
}

void Dwarf::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
    target.draw(animationStateText_, states);
}

void Dwarf::nextFrame()
{
    animationFrame_ += 1;
    // if past the final frame image
    if (animationFrame_ >= NUMBER_OF_FRAMES[animationState_])
    {
        animationFrame_ = 0;
        // if not infinite loop
        if (LOOP_AMOUNT[animationState_] > 0)
        {
            // if looped enough
            if (++animationLoopCount_ >= LOOP_AMOUNT[animationState_])
            {
                changeAnimation(AnimationState::IDLE);
            }
        }
    }
    // set the source rect of sprite
    const sf::IntRect rect = {animationFrame_ * SPRITE_WIDTH, SPRITE_Y_INDEX[animationState_] * SPRITE_HEIGHT,
                              SPRITE_WIDTH, SPRITE_HEIGHT};
    sprite_.setTextureRect(rect);
}

static void LogCommandCallStack(Dwarf::AnimationState animState);

void Dwarf::jump()
{
    if (animationState_ != AnimationState::JUMP)
    {
        changeAnimation(AnimationState::JUMP);
        LogCommandCallStack(AnimationState::JUMP);
    }
}

void Dwarf::weakAttack()
{
    if (animationState_ != AnimationState::WEAK_ATTACK)
    {
        changeAnimation(AnimationState::WEAK_ATTACK);
        LogCommandCallStack(AnimationState::WEAK_ATTACK);
    }
}

void Dwarf::strongAttack()
{
    if (animationState_ != AnimationState::STRONG_ATTACK)
    {
        changeAnimation(AnimationState::STRONG_ATTACK);
        LogCommandCallStack(AnimationState::STRONG_ATTACK);
    }
}

void Dwarf::specialAttack()
{
    if (animationState_ != AnimationState::SPECIAL_ATTACK)
    {
        changeAnimation(AnimationState::SPECIAL_ATTACK);
        LogCommandCallStack(AnimationState::SPECIAL_ATTACK);
    }
}

// Change the animation and reset frame & time to 0
void Dwarf::changeAnimation(AnimationState newAnimState)
{
    animationState_ = newAnimState;
    updateAnimationStateText(newAnimState);
    animationTimer_ = sf::Time::Zero;
    animationFrame_ = 0;
    animationLoopCount_ = 0;
    const sf::IntRect rect = {0, SPRITE_Y_INDEX[newAnimState] * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
    sprite_.setTextureRect(rect);
}

void Dwarf::updateAnimationStateText(AnimationState newAnimState)
{
    animationStateText_.setString(ANIM_STATE_STRS[newAnimState]);
    const sf::FloatRect bounds = animationStateText_.getLocalBounds();
    animationStateText_.setOrigin(bounds.width / 2, bounds.height / 2);
}

namespace
{
constexpr const char* TYPE_NAMES[Dwarf::AnimationState::TOTAL_COUNT_] = {"", "JumpCommand", "WeakAttackCommand",
                                                                         "StrongAttackCommand", "SpecialAttackCommand"};
constexpr const char* FUNC_NAMES[Dwarf::AnimationState::TOTAL_COUNT_] = {"", "jump", "weakAttack", "strongAttack",
                                                                         "specialAttack"};
constexpr const char* STATE_NAMES[Dwarf::AnimationState::TOTAL_COUNT_] = {"", "JUMP", "WEAK_ATTACK", "STRONG_ATTACK",
                                                                          "SPECIAL_ATTACK"};
} // namespace

static void LogCommandCallStack(Dwarf::AnimationState animState)
{
    global::logger->AddLog("=======================================================\n");
    global::logger->AddLog("<1> inputHandler_.handleInput() returns command object ptr\n");
    global::logger->AddLog("    Its actual type is %s*\n", TYPE_NAMES[animState]);
    global::logger->AddLog("<2> command->execute(*dwarf_) called\n");
    global::logger->AddLog("<3> %s::execute(*dwarf_) calls Dwarf::%s()\n", TYPE_NAMES[animState],
                           FUNC_NAMES[animState]);
    global::logger->AddLog("<4> Dwarf::changeAnimation(AnimationState::%s) called\n", STATE_NAMES[animState]);
}

} // namespace igpp::c02_01
