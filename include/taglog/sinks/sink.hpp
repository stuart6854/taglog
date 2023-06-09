#pragma once

#include <taglog/common.hpp>
#include <taglog/details/log_msg.hpp>

namespace TAGLOG_NAMESPACE
{
    namespace sinks
    {
        class Sink
        {
        public:
            virtual ~Sink() = default;

            virtual void log(const details::LogMsg& msg) = 0;
            virtual void flush() = 0;
        };
    }
}
