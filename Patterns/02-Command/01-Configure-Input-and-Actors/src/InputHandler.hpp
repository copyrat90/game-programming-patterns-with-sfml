#pragma once

#include <memory>

#include "Command.hpp"

namespace igpp::c02_01
{

class InputHandler
{
public:
    Command* handleInput();

private:
    std::unique_ptr<Command> buttonA_;
    std::unique_ptr<Command> buttonS_;
    std::unique_ptr<Command> buttonZ_;
    std::unique_ptr<Command> buttonX_;
};

} // namespace igpp::c02_01
