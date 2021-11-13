#pragma once

#include "Command.hpp"

namespace igpp::c02_01
{

class SpecialAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.specialAttack();
    }
};

} // namespace igpp::c02_01
