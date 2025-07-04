#pragma once

#include <unordered_map>
#include <filesystem>
#include <wrl/client.h>
#include "D2DRender.h"
#include "AnimationClip.h"

// 예시입니다.
class AssetManager
{
public:
    using AnimationClips = std::vector<std::pair<std::string, AnimationClip>>;
   
    AssetManager() = default;
    ~AssetManager() = default;

    void AddAsset(const std::filesystem::path& jsonPath, std::wstring key, sample::D2DRenderer* renderer);
    void AddTexture(const std::filesystem::path& texturePath, std::wstring key, sample::D2DRenderer* renderer);

    AnimationClips& GetClips(std::wstring key);
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetSpriteBitmap(std::wstring key);


private:
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_textures;
    std::unordered_map<std::wstring, AnimationClips> m_clipsMap;
};

