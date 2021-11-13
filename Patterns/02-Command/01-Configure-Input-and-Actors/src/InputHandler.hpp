#pragma once

#include <array>
#include <memory>

#include "Command.hpp"

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
    InputHandler();

    Command* handleInput();

private:
    std::array<const char*, TOTAL_COUNT_> keybindNames_;
    // Methods to bind commands...
    std::array<std::unique_ptr<Command>, TOTAL_COUNT_> buttons_;
};

} // namespace igpp::c02_01
