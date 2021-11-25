#pragma once

#include "Command.hpp"

namespace igpp::c02_01
{

// Snippet from the book
class JumpCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.jump();
    }
};

class SpecialAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.specialAttack();
    }
};

class StrongAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.strongAttack();
    }
};

class WeakAttackCommand final : public Command
{
public:
    void execute(GameActor& actor) final override
    {
        actor.weakAttack();
    }
};

} // namespace igpp::c02_01
