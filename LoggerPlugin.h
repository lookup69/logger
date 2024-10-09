/*
        2024-10-08
*/

#pragma once

#include <string>

namespace lkup69
{
enum LEVEL_E {
        INFO,
        WARN,
        ERR,
        NORMAL,
};

class LoggerPlugin
{
public:
        virtual void WriteLog(int level, const std::string &log) = 0;
        virtual ~LoggerPlugin()                                  = default;
};
}  // namespace lkup69