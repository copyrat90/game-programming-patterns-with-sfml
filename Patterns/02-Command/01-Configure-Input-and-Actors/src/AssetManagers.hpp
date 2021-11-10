#pragma once

#include "Common/AssetManager.hpp"

#include <SFML/Graphics.hpp>

namespace igpp::c02_01
{

enum class TextureId
{
    DWARF
};

using TextureManager = common::AssetManager<sf::Texture, TextureId>;

} // namespace igpp::c02_01
