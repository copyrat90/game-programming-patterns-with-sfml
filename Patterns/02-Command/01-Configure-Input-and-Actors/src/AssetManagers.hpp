#pragma once

#include "Common/AssetManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace igpp::c02_01
{

enum class TextureId
{
    DWARF
};

enum class FontId
{
    D2CODING
};

using TextureManager = common::AssetManager<sf::Texture, TextureId>;
using FontManager = common::AssetManager<sf::Font, FontId>;

} // namespace igpp::c02_01
