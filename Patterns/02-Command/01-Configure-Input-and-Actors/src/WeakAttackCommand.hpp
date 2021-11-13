#pragma once

#include "Command.hpp"

namespace igpp::c02_01
{

class WeakAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.weakAttack();
    }
};

} // namespace igpp::c02_01
