#pragma once

#include <array>
#include <memory>
#include <string>

#include "Command.hpp"

namespace sf
{
class Event;
}

namespace igpp::c02_01
{

// Snippet from the book, somewhat modified.
class InputHandler
{
public:
    enum Key
    {
        A,
        S,
        Z,
        X,
        TOTAL_COUNT_
    };

public:
    static constexpr const char KEY_CHARS[Key::TOTAL_COUNT_] = {'A', 'S', 'Z', 'X'};

public:
    InputHandler();

    Command* handleInput(const sf::Event&);

    void swapKeys(Key key1, Key key2);
    const Command* getBoundCommand(Key key) const;
    const std::string& getBoundCommandName(Key key) const;

private:
    // Methods to bind commands...
    std::array<std::unique_ptr<Command>, TOTAL_COUNT_> buttons_;

    std::array<std::string, TOTAL_COUNT_> commandNames_;
};

} // namespace igpp::c02_01
