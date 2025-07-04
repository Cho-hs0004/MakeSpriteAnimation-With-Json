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

void AssetManager::AddTexture(const std::filesystem::path& texturePath, std::wstring key, sample::D2DRenderer* renderer)
{
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

    renderer->CreateBitmapFromFile(texturePath.wstring().c_str(), *sheet.GetAddressOf());

    if (!sheet)
    {
        std::cerr << "비트맵 생성 오류" << std::endl;
        return;
    }

    if (m_textures.find(key) == m_textures.end());
        m_textures.emplace(key, sheet);
}

AnimationClips& AssetManager::GetClips(std::wstring key)
{
    if (m_clipsMap.find(key) == m_clipsMap.end())
    {
        std::cerr << "잘못된 키 입력" << std::endl;
    }
    return m_clipsMap.find(key)->second;
}

Microsoft::WRL::ComPtr<ID2D1Bitmap1> AssetManager::GetSpriteBitmap(std::wstring key)
{
    if (m_textures.find(key) == m_textures.end())
    {
        std::cerr << "잘못된 키 입력" << std::endl;
    }
    return m_textures.find(key)->second;
}
