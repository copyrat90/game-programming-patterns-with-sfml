#include "InputHandler.hpp"

#include <SFML/Window/Event.hpp>

#include "Commands.hpp"
#include "global.hpp"

namespace igpp::c02_01
{

InputHandler::InputHandler()
{
    buttons_[Key::Z] = std::make_unique<JumpCommand>();
    buttons_[Key::X] = std::make_unique<WeakAttackCommand>();
    buttons_[Key::A] = std::make_unique<StrongAttackCommand>();
    buttons_[Key::S] = std::make_unique<SpecialAttackCommand>();
    commandNames_[Key::Z] = "Jump";
    commandNames_[Key::X] = "Weak Attack";
    commandNames_[Key::A] = "Strong Attack";
    commandNames_[Key::S] = "Special Attack";
}

static void logCommandCallStack(InputHandler::Key key);

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
            logCommandCallStack(IHKey::A);
            return buttons_[IHKey::A].get();
        case SfKey::S:
            logCommandCallStack(IHKey::S);
            return buttons_[IHKey::S].get();
        case SfKey::Z:
            logCommandCallStack(IHKey::Z);
            return buttons_[IHKey::Z].get();
        case SfKey::X:
            logCommandCallStack(IHKey::X);
            return buttons_[IHKey::X].get();
        }
    }

    // Nothing pressed, so do nothing.
    return nullptr;
}

void InputHandler::swapKeys(Key key1, Key key2)
{
    buttons_[key1].swap(buttons_[key2]);
    commandNames_[key1].swap(commandNames_[key2]);
}

const Command* InputHandler::getBoundCommand(Key key) const
{
    return buttons_[key].get();
}

const std::string& InputHandler::getBoundCommandName(Key key) const
{
    return commandNames_[key];
}

static void logCommandCallStack(InputHandler::Key key)
{
    global::logger->AddLog("=======================================================\n");
    global::logger->AddLog("<1> inputHandler_.handleInput(event) returns buttons_[Key::%c].get()\n",
                           InputHandler::KEY_CHARS[key]);
}

} // namespace igpp::c02_01
