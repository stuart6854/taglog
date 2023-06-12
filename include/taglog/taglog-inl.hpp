#pragma once

#ifdef TAGLOG_HEADER_ONLY
    #include <taglog/taglog.hpp>
#endif

#include "common.hpp"

#include <set>
#include <ranges>
#include <format>
#include <string>
#include <functional>
#include <string_view>

#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

namespace TAGLOG_NAMESPACE
{
    void init() noexcept {}

    void terminate() noexcept {}

    auto gather_tags(TagsStringT tagsString) -> std::set<std::string_view>;
    auto format_tags(TagsStringT tagsString) -> std::string;

    template <typename... Args>
    void log(FormatStringT<Args...> fmt, Args&&... args) noexcept
    {
        const auto formattedTags = format_tags("");
        const auto formattedMsg = std::vformat(fmt, std::make_format_args(args...));

#ifdef _WIN32
//        OutputDebugStringA(formattedMsg.data());
//        ::WriteConsoleA()
#endif

        std::cout << "[" << formattedTags << "] " << formattedMsg << "\n";
    }

    template <typename... Args>
    void tagged_log(TagsStringT commaSeparatedTags, FormatStringT<Args...> fmt, Args&&... args) noexcept
    {
        const auto formattedTags = format_tags(commaSeparatedTags);
        const auto formattedMsg = std::vformat(fmt, std::make_format_args(args...));

        std::cout << "[" << formattedTags << "] " << formattedMsg << "\n";
    }

    struct LogTag
    {
        std::string tag{};
        Color bgColor{ Color::eNone };
        Color fgColor{ Color::eNone };
    };
    inline static std::unordered_map<std::size_t, LogTag> s_logTags{};
    inline static std::set<std::string_view> s_activeTags{};

    void define_tag(std::string_view tag, Color fgColor, Color bgColor) noexcept
    {
        const auto tagHash = std::hash<std::string_view>{}(std::string_view(tag));
        s_logTags[tagHash] = LogTag{ std::string(tag), bgColor, fgColor };
    }

    void begin_tag(std::string_view tag) noexcept
    {
        s_activeTags.insert(tag);
    }

    void end_tag(std::string_view tag) noexcept
    {
        s_activeTags.erase(tag);
    }

// clang-format off
#if 0
//#ifdef _WIN32
    // Windows
    #define COLOR_FG_BLACK   0
    #define COLOR_FG_RED     FOREGROUND_RED
    #define COLOR_FG_GREEN   FOREGROUND_GREEN
    #define COLOR_FG_BLUE    FOREGROUND_BLUE
    #define COLOR_FG_YELLOW  (FOREGROUND_RED | FOREGROUND_GREEN)
    #define COLOR_FG_MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
    #define COLOR_FG_CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE)
    #define COLOR_FG_WHITE   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
    #define COLOR_FB_BOLD        FOREGROUND_INTENSITY

    #define COLOR_BG_BLACK   0
    #define COLOR_BG_RED     BACKGROUND_RED
    #define COLOR_BG_GREEN   BACKGROUND_GREEN
    #define COLOR_BG_BLUE    BACKGROUND_BLUE
    #define COLOR_BG_YELLOW  (BACKGROUND_RED | BACKGROUND_GREEN)
    #define COLOR_BG_MAGENTA (BACKGROUND_RED | BACKGROUND_BLUE)
    #define COLOR_BG_CYAN    (BACKGROUND_GREEN | BACKGROUND_BLUE)
    #define COLOR_BG_WHITE   (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
    #define COLOR_BB_BOLD    BACKGROUND_INTENSITY
//#else
#endif
    // Ubuntu/Linux/MacOS
    #define COLOR_RESET   "\033[0m"
    #define COLOR_BLACK   "\033[30m"      /* Black */
    #define COLOR_RED     "\033[31m"      /* Red */
    #define COLOR_GREEN   "\033[32m"      /* Green */
    #define COLOR_YELLOW  "\033[33m"      /* Yellow */
    #define COLOR_BLUE    "\033[34m"      /* Blue */
    #define COLOR_MAGENTA "\033[35m"      /* Magenta */
    #define COLOR_CYAN    "\033[36m"      /* Cyan */
    #define COLOR_WHITE   "\033[37m"      /* White */
    #define COLOR_BOLD_BLACK   "\033[1m\033[30m"      /* Bold Black */
    #define COLOR_BOLD_RED     "\033[1m\033[31m"      /* Bold Red */
    #define COLOR_BOLD_GREEN   "\033[1m\033[32m"      /* Bold Green */
    #define COLOR_BOLD_YELLOW  "\033[1m\033[33m"      /* Bold Yellow */
    #define COLOR_BOLD_BLUE    "\033[1m\033[34m"      /* Bold Blue */
    #define COLOR_BOLD_MAGENTA "\033[1m\033[35m"      /* Bold Magenta */
    #define COLOR_BOLD_CYAN    "\033[1m\033[36m"      /* Bold Cyan */
    #define COLOR_BOLD_WHITE   "\033[1m\033[37m"      /* Bold White */
//#endif
    // clang-format on

    auto gather_tags(TagsStringT tagsString) -> std::set<std::string_view>
    {
        auto outputTags = s_activeTags;
        for (const auto tag : std::ranges::views::split(tagsString, ','))
        {
            outputTags.insert(std::string_view(tag));
        }
        return outputTags;
    }

    auto format_tags(TagsStringT tagsString) -> std::string
    {
        auto tags = gather_tags(tagsString);
        if (tags.empty())
        {
            return "";
        }

        std::string buffer;
        for (const auto tag : tags)
        {
            auto tagHash = std::hash<std::string_view>{}(std::string_view(tag));

            std::string colorBegStr{};
            std::string colorEndStr{};

            const auto it = s_logTags.find(tagHash);
            if (it != s_logTags.end())
            {
                const auto& color = it->second;
                colorBegStr = COLOR_RED;
                colorEndStr = COLOR_RESET;
            }

            auto formattedTag = std::format("{}#{}{}", colorBegStr, std::string_view(tag), colorEndStr);
            buffer.append(formattedTag);
            buffer.push_back(' ');
        }
        buffer.erase(buffer.end() - 1);  // Remove leading space

        return buffer;
    }

}