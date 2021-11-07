// This source is a modified version of ResourceHolder from:
// https://github.com/SFML/SFML-Game-Development-Book/blob/master/02_Resources/Include/Book/ResourceHolder.inl
// So, it is licensed under this license file:
// https://github.com/SFML/SFML-Game-Development-Book/blob/master/License.txt

namespace igpp::common
{

template <typename Asset, typename AssetId>
inline void AssetManager<Asset, AssetId>::load(AssetId id, const std::string& filePath)
{
    auto asset = std::make_unique<Asset>();
    if (!asset->loadFromFile(filePath))
        throw std::runtime_error("Can't load asset: " + filePath);
    insertToMap(id, std::move(asset));
}

template <typename Asset, typename AssetId>
template <typename Param>
inline void AssetManager<Asset, AssetId>::load(AssetId id, const std::string& filePath, const Param& additionalParam)
{
    auto asset = std::make_unique<Asset>();
    if (!asset->loadFromFile(filePath, additionalParam))
        throw std::runtime_error("Can't load asset: " + filePath);
    insertToMap(id, std::move(asset));
}

template <typename Asset, typename AssetId>
inline Asset& AssetManager<Asset, AssetId>::get(AssetId id)
{
    auto found = assetMap_.find(id);
    assert(found != assetMap_.end());
    return *found->second;
}

template <typename Asset, typename AssetId>
inline const Asset& AssetManager<Asset, AssetId>::get(AssetId id) const
{
    auto found = assetMap_.find(id);
    assert(found != assetMap_.cend());
    return *found->second;
}

template <typename Asset, typename AssetId>
inline void igpp::common::AssetManager<Asset, AssetId>::insertToMap(AssetId id, std::unique_ptr<Asset> asset)
{
    assert(assetMap_.find(id) == assetMap_.cend());
    assetMap_.emplace(id, std::move(asset));
}

} // namespace igpp::common
