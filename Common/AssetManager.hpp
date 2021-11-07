// This source is a modified version of ResourceHolder from:
// https://github.com/SFML/SFML-Game-Development-Book/blob/master/02_Resources/Include/Book/ResourceHolder.hpp
// So, it is licensed under this license file:
// https://github.com/SFML/SFML-Game-Development-Book/blob/master/License.txt

#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace igpp::common
{

template <typename Asset, typename AssetId>
class AssetManager
{
public:
    void load(AssetId id, const std::string& filePath);
    template <typename Param>
    void load(AssetId id, const std::string& filePath, const Param& additionalParam);

    Asset& get(AssetId id);
    const Asset& get(AssetId id) const;

private:
    void insertToMap(AssetId id, std::unique_ptr<Asset> asset);

private:
    std::map<AssetId, std::unique_ptr<Asset>> assetMap_;
};

} // namespace igpp::common

#include "AssetManager.inl"
