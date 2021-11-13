#pragma once

#include "Command.hpp"

namespace igpp::c02_01
{

class StrongAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.strongAttack();
    }
};

} // namespace igpp::c02_01
