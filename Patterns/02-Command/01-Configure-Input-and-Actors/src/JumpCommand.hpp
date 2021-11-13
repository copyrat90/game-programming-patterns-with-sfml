#pragma once

#include "Command.hpp"

namespace igpp::c02_01
{

class JumpCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.jump();
    }
};

} // namespace igpp::c02_01
