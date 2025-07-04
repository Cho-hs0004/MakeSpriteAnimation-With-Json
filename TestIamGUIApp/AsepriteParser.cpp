#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "AsepriteParser.h"

struct FrameTag {
    std::string tag;
    int from;
    int to;
};

AnimationClips AsepriteParser::Load(const std::filesystem::path& jsonPath)
{
    // 1) JSON 로드하세요.
    std::ifstream ifs(jsonPath);

    if (!ifs.is_open())
    {
        std::cerr << "Json 파일을 열 수 없습니다." << std::endl;
        return {};
    }

    nlohmann::json js;
    ifs >> js;  //파일을 json타입으로 parse

    if (js.is_discarded())
    {
        std::cerr << "JSON 파싱 실패: 유효하지 않은 문서입니다.\n";
        return {};
    }

    std::vector<FrameTag> frametags;

    for (const auto& t : js["meta"]["frameTags"])
    {
        FrameTag tag;
        tag.tag = t["name"];
        tag.from = t["from"];
        tag.to = t["to"];

        frametags.push_back(tag);
    }

    // 2) 태그별로  AnimationClips 생성합니다.
    AnimationClips clips;

    for (const auto& tag : frametags)
    {
        AnimationClip clip;

        for (int i = tag.from; i <= tag.to; i++)
        {
            auto& frame = js["frames"][i];
            Frame src;
            src.srcRect.top = frame["frame"]["y"];
            src.srcRect.bottom = src.srcRect.top + frame["frame"]["h"];
            src.srcRect.left = frame["frame"]["x"];
            src.srcRect.right = src.srcRect.left + frame["frame"]["w"];
            src.duration = frame["duration"]/1000.0f;

            clip.AddFrame(src);
        }

        std::pair j = { tag.tag, clip };
        clips.push_back(j);
    }

    return clips;
}
