#pragma once

#include <taglog/common.hpp>
#include <taglog/details/log_msg.hpp>

#include <memory>

namespace TAGLOG_NAMESPACE
{
    class Sink;

    class Logger
    {
    public:
        explicit Logger(std::string name) : m_name(std::move(name)) {}

        virtual ~Logger() = default;

        /* Methods */

        template <typename... Args>
        void log(SourceLoc loc, FormatStringT<Args...> fmt, Args&&... args)
        {
            log_(loc, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void log_(SourceLoc loc, FormatStringT<Args...> fmt, Args&&... args)
        {
            std::string buffer;
            std::vformat_to(std::back_inserter(buffer), fmt, std::make_format_args(args...));

            details::LogMsg logMsg(loc, m_name, std::string_view(buffer));
            log_it_(logMsg);
        }

        /* Getters */

        auto name() const -> const std::string&;
        auto sinks() const -> const std::vector<SinkPtr>&;

    protected:
        void log_it_(const details::LogMsg& logMsg);
        void sink_it_(const details::LogMsg& logMsg);

    protected:
        std::string m_name;
        std::vector<SinkPtr> m_sinks;
    };
}

#ifdef TAGLOG_HEADER_ONLY
    #include "logger-inl.hpp"
#endif