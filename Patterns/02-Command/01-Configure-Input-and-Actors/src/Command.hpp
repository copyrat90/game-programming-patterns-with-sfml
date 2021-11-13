#pragma once

#include "GameActor.hpp"

namespace igpp::c02_01
{

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(GameActor&) = 0;
};

} // namespace igpp::c02_01
