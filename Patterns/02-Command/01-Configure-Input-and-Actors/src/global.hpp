#pragma once

#include <optional>

#include "Common/ImguiLogger.hpp"

namespace igpp::common
{
class ImguiLogger;
}

namespace igpp::c02_01::global
{

extern std::optional<common::ImguiLogger> logger;

}
