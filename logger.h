/*
        2024-05-24
*/

#pragma once

#include <sstream>
#include <memory>
#include <vector>
#include <mutex>

namespace lkup69
{
class Logger
{
        Logger(const Logger &)            = delete;
        Logger &operator=(const Logger &) = delete;

public:
        template <typename T>
        static void Log(const T &msg)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::NOMARL>(msg);
        }

        template <typename T>
        static void Info(const T &msg)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::INFO>(msg);
        }

        template <typename T>
        static void Warn(const T &msg)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::WARN>(msg);
        }

        template <typename T>
        static void Err(const T &msg)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::ERR>(msg);
        }

        template <typename Format, typename... Args>
        static void Log(Format format, Args... args)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::NOMARL>(format, args...);
        }

        template <typename Format, typename... Args>
        static void Info(Format format, Args... args)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::INFO>(format, args...);
        }

        template <typename Format, typename... Args>
        static void Warn(Format format, Args... args)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::WARN>(format, args...);
        }

        template <typename Format, typename... Args>
        static void Err(Format format, Args... args)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::ERR>(format, args...);
        }

        static Logger &GetInstance()
        {
                static Logger logger;

                return logger;
        }

        static void RegisterLogPlugin(std::unique_ptr<LoggerPlugin> &&plugin)
        {
                Logger::GetInstance().RegisterLogPlugin_(std::move(plugin));
        }

private:
        Logger()  = default;
        ~Logger() = default;

        void RegisterLogPlugin_(std::unique_ptr<LoggerPlugin> &&plugin);

        template <int Level = 0, typename T>
        void WriteLog_(const T &msg)
        {
                const std::lock_guard<std::mutex> lock(m_selfLock);

                if (m_pluginVec.empty())
                        return;

                std::stringstream ss;
                std::string       lineHeader;

                ss << msg;
                if (Level == INFO)
                        lineHeader = "[info]";
                else if (Level == WARN)
                        lineHeader = "[warn]";
                else if (Level == ERR)
                        lineHeader = "[err]";
                lineHeader += ss.str();

                for (const auto &plugin : m_pluginVec)
                        plugin->WriteLog(Level, lineHeader);
        }

        template <int Level = 0, typename Format, typename... Args>
        void WriteLog_(Format format, Args &...args)
        {
                const std::lock_guard<std::mutex> lock(m_selfLock);

                if (m_pluginVec.empty())
                        return;

                char buf[4096] = { 0 };
                int  off       = 0;
                std::string lineHeader;

                if (Level == INFO)
                        lineHeader = "[info]";
                else if (Level == WARN)
                        lineHeader = "[warn]";
                else if (Level == ERR)
                        lineHeader = "[err]";

                off = snprintf(buf, lineHeader.size() + 1, "%s", lineHeader.c_str());
                snprintf((buf + off), sizeof(buf) - off - 1, format, args...);

                for (const auto &plugin : m_pluginVec)
                        plugin->WriteLog(Level, buf);
        }

private:
        std::vector<std::unique_ptr<LoggerPlugin>> m_pluginVec;
        std::mutex                                 m_selfLock;
        bool                                       m_bDateTime = true;
};

}  // namespace lkup69

#define log_info(format, ...) lkup69::Logger::Info("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define log_warn(format, ...) lkup69::Logger::Warn("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define log_err(format, ...)  lkup69::Logger::Err("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
