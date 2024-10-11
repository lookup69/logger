/*
        2024-05-24
*/

#pragma once

#include <sstream>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iomanip>

#include "LoggerPlugin.h"

namespace lkup69
{
class Logger
{
        struct LogQueueElm {
                int         level;
                std::string msg;
        };

        Logger(const Logger &)            = delete;
        Logger &operator=(const Logger &) = delete;

public:
        template <typename T>
        static void Log(const T &msg)
        {
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::NORMAL>(msg);
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
                lkup69::Logger::GetInstance().WriteLog_<LEVEL_E::NORMAL>(format, args...);
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
        Logger()  
        {
                m_workThread = std::thread{&Logger::WriteLogThread_, this};
        }

        ~Logger() 
        {
                m_bExit =  true;

                m_workThread.join();
        }

        void RegisterLogPlugin_(std::unique_ptr<LoggerPlugin> &&plugin);

        void WriteLogThread_()
        {
                while (!m_bExit) {
                        std::unique_lock<std::mutex> lck(m_selfLock);

                        m_cv.wait(lck);

                        while (!m_logQueue.empty()) {
                                LogQueueElm logElm;

                                {
                                        const std::lock_guard<std::mutex> lock(m_writeLoke);

                                        logElm = std::move(m_logQueue.front());
                                        m_logQueue.pop();
                                }

                                for (const auto &plugin : m_pluginVec)
                                        plugin->WriteLog(logElm.level, logElm.msg);
                        }

                        lck.unlock();
                }
        }

        template <int Level = 0, typename T>
        void WriteLog_(const T &log)
        {
                if (m_pluginVec.empty())
                        return;
                const std::lock_guard<std::mutex> lock(m_writeLoke);

                auto               now        = std::chrono::system_clock::now();
                std::time_t        now_c      = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
                std::tm           *local_time = std::localtime(&now_c);
                std::ostringstream oss;
                LogQueueElm        logElm;

                oss << "[" << std::put_time(local_time, "%Y%m%d %H:%M:%S") << "]";

                if (Level == INFO)
                        oss << "[info]";
                else if (Level == WARN)
                        oss << "[warn]";
                else if (Level == ERR)
                        oss << "[err]";

                //oss << " " << log;
                oss << log;

                logElm.msg   = std::move(oss.str());
                logElm.level = Level;

#if 1
                m_logQueue.push(logElm);
                m_cv.notify_all();
#else
                for (const auto &plugin : m_pluginVec)
                        plugin->WriteLog(logElm.level, logElm.msg);
#endif                        
        }

        template <int Level = 0, typename Format, typename... Args>
        void WriteLog_(Format format, Args &...args)
        {
                if (m_pluginVec.empty())
                        return;
                const std::lock_guard<std::mutex> lock(m_writeLoke);

                char        buf[4096] = { 0 };
                int         off       = 0;
                std::string lineHeader;
                LogQueueElm logElm;

                if (Level == INFO)
                        lineHeader = "[info]";
                else if (Level == WARN)
                        lineHeader = "[warn]";
                else if (Level == ERR)
                        lineHeader = "[err]";

                off = snprintf(buf, lineHeader.size() + 1, "%s", lineHeader.c_str());
                snprintf((buf + off), sizeof(buf) - off - 1, format, args...);

                auto               now        = std::chrono::system_clock::now();
                std::time_t        now_c      = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
                std::tm           *local_time = std::localtime(&now_c);
                std::ostringstream oss;

                oss << "[" << std::put_time(local_time, "%Y%m%d %H:%M:%S") << "]";
                logElm.msg.append(oss.str());
                logElm.msg.append(buf);
                logElm.level = Level;

                if (logElm.msg.at(logElm.msg.size() - 1) != '\n')
                        logElm.msg.push_back('\n');
#if 1
                m_logQueue.push(logElm);
                m_cv.notify_all();
#else                
                for (const auto &plugin : m_pluginVec)
                        plugin->WriteLog(logElm.level, logElm.msg);
#endif                        
        }

private:
        std::mutex                                 m_selfLock;
        std::mutex                                 m_writeLoke;
        std::vector<std::unique_ptr<LoggerPlugin>> m_pluginVec;
        std::queue<LogQueueElm>                    m_logQueue;
        std::thread                                m_workThread;
        bool                                       m_bDateTime = true;
        bool                                       m_bExit     = false;
        std::condition_variable                    m_cv;
};

}  // namespace lkup69

#define log_info_f(format, ...)   lkup69::Logger::Info("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define log_warn_f(format, ...)   lkup69::Logger::Warn("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define log_err_f(format, ...)    lkup69::Logger::Err("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define log_normal_f(format, ...) lkup69::Logger::Log("[%s][%s][%d] " format, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#define log_info(format, ...)     lkup69::Logger::Info(" " format, ##__VA_ARGS__)
#define log_warn(format, ...)     lkup69::Logger::Warn(" " format, ##__VA_ARGS__)
#define log_err(format, ...)      lkup69::Logger::Err(" " format, ##__VA_ARGS__)
#define log_normal(format, ...)   lkup69::Logger::Log(" " format, ##__VA_ARGS__)
