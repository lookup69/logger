/*
        2024-05-24
*/

#include "logger.h"

using namespace lkup69;

void Logger::RegisterLogPlugin_(std::unique_ptr<LoggerPlugin> &&plugin)
{
        const std::lock_guard<std::mutex> lock(m_selfLock);

        m_pluginVec.emplace_back(std::move(plugin));
}




