#pragma once

#include "GameActor.hpp"

namespace igpp::c02_01
{

// Snippet from the book
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute(GameActor&) = 0;
};

} // namespace igpp::c02_01
