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
        KEY_COUNT
    };

public:
    InputHandler();

    Command* handleInput();

private:
    std::array<const char*, KEY_COUNT> keybindNames_;
    // Methods to bind commands...
    std::array<std::unique_ptr<Command>, KEY_COUNT> buttons_;
};

} // namespace igpp::c02_01
