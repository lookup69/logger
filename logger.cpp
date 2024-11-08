/*
        2024-05-24
*/

#include "logger.h"

#include <algorithm>

using namespace lkup69;

void Logger::RegisterLogPlugin_(std::unique_ptr<LoggerPlugin> &&plugin, const std::string &name)
{
        const std::lock_guard<std::mutex> lock(m_plugInLock);

        auto it = find_if(m_pluginVec.begin(), m_pluginVec.end(), [&name](const PluginInElm &elm) {
                if (elm.name.compare(name) == 0)
                        return true;
                return false;
        });

        if (it != m_pluginVec.end())
                return;

        m_pluginVec.emplace_back(PluginInElm{ .name = name, .plugin = std::move(plugin) });
}

void Logger::EnablePlugin_(const std::string &name)
{
        const std::lock_guard<std::mutex> lock(m_plugInLock);

        auto it = find_if(m_pluginVec.begin(), m_pluginVec.end(), [&name](const PluginInElm &elm) {
                if (elm.name.compare(name) == 0)
                        return true;
                return false;
        });

        if (it != m_pluginVec.end())
                it->enable = true;

}

void Logger::DisablePlugin_(const std::string &name)
{
        const std::lock_guard<std::mutex> lock(m_plugInLock);

        auto it = find_if(m_pluginVec.begin(), m_pluginVec.end(), [&name](const PluginInElm &elm) {
                if (elm.name.compare(name) == 0)
                        return true;
                return false;
        });

        if (it != m_pluginVec.end())
                it->enable = false;

}

void Logger::WriteLogThread_()
{
        while (!m_bExit) {
                std::unique_lock<std::mutex> notifyLock(m_flushNotifyLock);

                m_flushNotify.wait(notifyLock);

                while (!m_logQueue.empty()) {
                        LogQueueElm logElm;

                        {
                                const std::lock_guard<std::mutex> lock(m_writeLock);

                                logElm = std::move(m_logQueue.front());
                                m_logQueue.pop();
                        }

                        const std::lock_guard<std::mutex> lock(m_plugInLock);
                        for (const auto &elm : m_pluginVec)
                                if (elm.enable)
                                        elm.plugin->WriteLog(logElm.level, logElm.msg);
                }

                notifyLock.unlock();
        }
}
