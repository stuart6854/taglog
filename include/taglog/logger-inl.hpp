#pragma once

#ifdef TAGLOG_HEADER_ONLY
    #include <taglog/logger.hpp>
#endif

#include <taglog/sinks/sink.hpp>

namespace TAGLOG_NAMESPACE
{
    void Logger::log_it_(const details::LogMsg& logMsg)
    {
        sink_it_(logMsg);
    }

    void Logger::sink_it_(const details::LogMsg& logMsg)
    {
        for (auto& sink : m_sinks)
        {
            sink->log(logMsg);
        }
    }
}