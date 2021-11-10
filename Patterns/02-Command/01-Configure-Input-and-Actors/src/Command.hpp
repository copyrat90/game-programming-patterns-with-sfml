#pragma once

namespace igpp::c02_01
{

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

} // namespace igpp::c02_01
