#include "InputHandler.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "JumpCommand.hpp"
#include "SpecialAttackCommand.hpp"
#include "StrongAttackCommand.hpp"
#include "WeakAttackCommand.hpp"

namespace igpp::c02_01
{

InputHandler::InputHandler()
{
    buttons_[Key::Z] = std::make_unique<JumpCommand>();
    buttons_[Key::X] = std::make_unique<WeakAttackCommand>();
    buttons_[Key::A] = std::make_unique<StrongAttackCommand>();
    buttons_[Key::S] = std::make_unique<SpecialAttackCommand>();
}

// Snippet from the book, somewhat modified.
Command* InputHandler::handleInput()
{
    using KB = sf::Keyboard;
    if (KB::isKeyPressed(KB::A))
        return buttons_[Key::A].get();
    if (KB::isKeyPressed(KB::S))
        return buttons_[Key::S].get();
    if (KB::isKeyPressed(KB::Z))
        return buttons_[Key::Z].get();
    if (KB::isKeyPressed(KB::X))
        return buttons_[Key::X].get();

    // Nothing pressed, so do nothing.
    return nullptr;
}

} // namespace igpp::c02_01
