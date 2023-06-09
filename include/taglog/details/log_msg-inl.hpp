#pragma once

#ifdef TAGLOG_HEADER_ONLY
    #include <taglog/details/log_msg.hpp>
#endif

#include <thread>

namespace TAGLOG_NAMESPACE
{
    namespace details
    {
        LogMsg::LogMsg(LogClock::time_point logTime, std::source_location loc, std::string_view loggerName, std::string_view msg)
            : time(logTime), threadId(std::this_thread::get_id()), sourceLocation(loc), loggerName(loggerName), msg(msg)
        {
        }

        LogMsg::LogMsg(std::source_location loc, std::string_view loggerName, std::string_view msg)
            : sourceLocation(loc), loggerName(loggerName), msg(msg)
        {
        }

        LogMsg::LogMsg(std::string_view loggerName, std::string_view msg) : loggerName(loggerName), msg(msg) {}
    }
}