#pragma once

#include <taglog/common.hpp>

#include <string>
#include <stacktrace>
#include <source_location>

namespace TAGLOG_NAMESPACE
{
    namespace details
    {
        struct LogMsg
        {
            LogMsg() = default;
            LogMsg(LogClock::time_point logTime, std::source_location loc, std::string_view loggerName, std::string_view msg);
            LogMsg(std::source_location loc, std::string_view loggerName, std::string_view msg);
            LogMsg(std::string_view loggerName, std::string_view msg);
            LogMsg(const LogMsg& other) = default;
            auto operator=(const LogMsg& other) -> LogMsg& = default;

            std::string_view loggerName;
            LogClock::time_point time;
            std::thread::id threadId;

            std::stacktrace stackTrace;
            std::source_location sourceLocation;
            std::string_view msg;
        };
    }
}

#ifdef TAGLOG_HEADER_ONLY
    #include "log_msg-inl.hpp"
#endif