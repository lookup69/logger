/*
        2024-05-24
*/

#pragma once

#include "LoggerPlugin.h"

#include <unistd.h>

#include <vector>

namespace lkup69
{
class FileLogPlugin : public LoggerPlugin
{
private:
        FileLogPlugin(const FileLogPlugin &)                  = delete;
        const FileLogPlugin &operator=(const FileLogPlugin &) = delete;
        FileLogPlugin(const std::string &file, size_t maxLines);

public:
        virtual ~FileLogPlugin() = default;

public:
        static FileLogPlugin *CreatePluginIns(const std::string &file, size_t maxLines = 1000);

public:
        void WriteLog(LEVEL_E level, const std::string &log) override;

private:
        std::string              m_file;
        size_t                   m_maxLines;
        std::vector<std::string> m_logVec;
};
}  // namespace lkup69
