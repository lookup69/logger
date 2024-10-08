/*
        2024-05-24
*/

#pragma once

#include "LoggerPlugin.h"

namespace lkup69
{
class ConsoleLogPlugin : public LoggerPlugin
{
        ConsoleLogPlugin(const ConsoleLogPlugin &)                  = delete;
        const ConsoleLogPlugin &operator=(const ConsoleLogPlugin &) = delete;
        ConsoleLogPlugin()          = default;
public:
        virtual ~ConsoleLogPlugin() = default;

public:
        static ConsoleLogPlugin *CreatePluginIns()
        {
                return new (std::nothrow) ConsoleLogPlugin{};
        }

public:
        void WriteLog(int level, const std::string &log) override;
};
}  // namespace lkup69
