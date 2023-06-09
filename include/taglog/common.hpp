#pragma once

#include <chrono>
#include <stacktrace>
#include <string_view>
#include <source_location>

#define TAGLOG_NAMESPACE taglog

namespace TAGLOG_NAMESPACE
{
    template <typename... Args>
    using FormatStringT = std::string_view;

    using TagsStringT = std::string_view;

    using LogClock = std::chrono::high_resolution_clock;

    using SourceLoc = std::source_location;
    using StackTrace = std::stacktrace;

    namespace sinks
    {
        class Sink;
    }
    using SinkPtr = std::shared_ptr<sinks::Sink>;

}
