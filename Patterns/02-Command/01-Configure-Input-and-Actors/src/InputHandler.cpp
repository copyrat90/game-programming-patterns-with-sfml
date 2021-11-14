#include "InputHandler.hpp"

#include <SFML/Window/Event.hpp>

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
Command* InputHandler::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            using SfKey = sf::Keyboard::Key;
            using IHKey = InputHandler::Key;
        case SfKey::A:
            return buttons_[IHKey::A].get();
        case SfKey::S:
            return buttons_[IHKey::S].get();
        case SfKey::Z:
            return buttons_[IHKey::Z].get();
        case SfKey::X:
            return buttons_[IHKey::X].get();
        }
    }

    // Nothing pressed, so do nothing.
    return nullptr;
}

} // namespace igpp::c02_01
