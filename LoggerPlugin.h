/*
        2024-10-08
*/

#pragma once

#include <string>

namespace lkup69
{
enum class LEVEL_E {
        INFO,
        TRACE,
        WARN,
        ERR,
        NORMAL,
};

class LoggerPlugin
{
public:
        virtual void WriteLog(LEVEL_E level, const std::string &log) = 0;
        virtual ~LoggerPlugin()                                      = default;
};
}  // namespace lkup69