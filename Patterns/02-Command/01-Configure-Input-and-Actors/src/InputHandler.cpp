#include "InputHandler.hpp"

#include <SFML/Window/Keyboard.hpp>

namespace igpp::c02_01
{

Command* InputHandler::handleInput()
{
    using KB = sf::Keyboard;
    if (KB::isKeyPressed(KB::A))
        return buttonA_.get();
    if (KB::isKeyPressed(KB::S))
        return buttonS_.get();
    if (KB::isKeyPressed(KB::Z))
        return buttonZ_.get();
    if (KB::isKeyPressed(KB::X))
        return buttonX_.get();

    return nullptr;
}

} // namespace igpp::c02_01
