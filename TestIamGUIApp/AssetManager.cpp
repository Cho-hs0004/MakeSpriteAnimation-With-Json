#include "pch.h"
#include "AnimationClip.h"
#include "AsepriteParser.h"
#include "AssetManager.h"

void AssetManager::AddAsset(const std::filesystem::path& jsonPath, std::wstring key, sample::D2DRenderer* renderer)
{
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

    std::filesystem::path texturePath = jsonPath;
    texturePath.replace_extension(".png");

    renderer->CreateBitmapFromFile(texturePath.wstring().c_str(), *sheet.GetAddressOf());

    if (!sheet)
    {
        std::cerr << "비트맵 생성 오류" << std::endl;
        return;
    }

    AnimationClips clips = AsepriteParser::Load(jsonPath);

    for (auto& clip : clips)
    {
        clip.second.SetBitmap(sheet);
    }

    m_textures.emplace(key, sheet);
    m_clipsMap.emplace(key, clips);
}

AnimationClips& AssetManager::GetClips(std::wstring key)
{
    std::cout << &m_clipsMap.find(key)->second << std::endl;
    return m_clipsMap.find(key)->second;
}
