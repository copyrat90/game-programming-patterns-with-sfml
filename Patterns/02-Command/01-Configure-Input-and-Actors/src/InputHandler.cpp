#include "InputHandler.hpp"

#include <SFML/Window/Event.hpp>
#include <stdexcept>
#include <string>

#include "Commands.hpp"
#include "global.hpp"

namespace igpp::c02_01
{

sf::Keyboard::Key InputHandler::convertIHKeyToSfKey(InputHandler::Key ihKey)
{
    using IHKey = InputHandler::Key;
    using SfKey = sf::Keyboard::Key;

    switch (ihKey)
    {
    case IHKey::A:
        return SfKey::A;
    case IHKey::S:
        return SfKey::S;
    case IHKey::Z:
        return SfKey::Z;
    case IHKey::X:
        return SfKey::X;
    }
    throw std::invalid_argument("Invalid InputHandler::Key : " + std::to_string(ihKey) + "given");
}

InputHandler::Key InputHandler::convertSfKeyToIHKey(sf::Keyboard::Key sfKey)
{
    using SfKey = sf::Keyboard::Key;
    using IHKey = InputHandler::Key;

    switch (sfKey)
    {
    case SfKey::A:
        return IHKey::A;
    case SfKey::S:
        return IHKey::S;
    case SfKey::Z:
        return IHKey::Z;
    case SfKey::X:
        return IHKey::X;
    }
    throw std::invalid_argument("Invalid sf::Keyboard::Key : " + std::to_string(sfKey) + "given");
}

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
        case SfKey::S:
        case SfKey::Z:
        case SfKey::X:
            IHKey key = convertSfKeyToIHKey(event.key.code);
            logCommandCallStack(key);
            return buttons_[key].get();
        }
    }

    // Nothing pressed, so do nothing.
    return nullptr;
} // namespace igpp::c02_01

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
