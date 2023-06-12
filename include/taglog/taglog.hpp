// TagLog main header file.

#ifndef TAGLOG_H
#define TAGLOG_H

#pragma once

#include <taglog/common.hpp>
#include <taglog/logger.hpp>

#include <iostream>
#include <format>
#include <string>
#include <string_view>
#include <unordered_map>

/*
 * Example Logs:
 *  - Format: [%date% - %time%] %tags% %msg%
 *      - [08/06/23 - 13:56:45.435ms] #info #network #connection User has connected.
 *      - [08/06/23 - 13:56:45.435ms] #error #system #rendering #backend #memory Graphics device was unable to allocate memory!
 */

// Coloured output
//  - https://dev.to/tenry/terminal-colors-in-c-c-3dgc
//  - Windows: https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
//  - ANSI: https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html

#ifdef _WIN32
// #include <wincon.h>

// Avoid including windows.h (https://stackoverflow.com/a/30741042)
// extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char* lpOutputString);
#endif

namespace TAGLOG_NAMESPACE
{
    enum class Color
    {
        eNone,
        eBlack,
        eWhite,
        eRed,
        eGreen,
        eBlue,
        eYellow,
        eMagenta,
        eCyan,
        eBrightBlack,
        eBrightWhite,
        eBrightRed,
        eBrightGreen,
        eBrightBlue,
        eBrightYellow,
        eBrightMagenta,
        eBrightCyan,
    };

    void init() noexcept;
    void terminate() noexcept;

    void define_tag(std::string_view tag, Color fgColor, Color bgColor) noexcept;

    void begin_tag(std::string_view tag) noexcept;
    void end_tag(std::string_view tag) noexcept;

    template <typename... Args>
    inline void log(FormatStringT<Args...> fmt, Args&&... args) noexcept;

    template <typename... Args>
    inline void tagged_log(TagsStringT commaSeparatedTags, FormatStringT<Args...> fmt, Args&&... args) noexcept;

    /**
     * Scoped-based Tag that begins when the object constructor and ends when the object is destroyed.
     */
    struct ScopedTag
    {
        ScopedTag(std::string_view tag) : m_tag(tag) { begin_tag(m_tag); }
        ~ScopedTag() { end_tag(m_tag); }

        ScopedTag(const ScopedTag&) = delete;
        ScopedTag(ScopedTag&&) noexcept = delete;

        auto operator=(const ScopedTag&) -> ScopedTag& = delete;
        auto operator=(ScopedTag&&) noexcept -> ScopedTag& = delete;

    private:
        std::string_view m_tag;
    };

}

#ifdef TAGLOG_HEADER_ONLY
    #include "taglog-inl.hpp"
#endif

#endif  // TAGLOG_H