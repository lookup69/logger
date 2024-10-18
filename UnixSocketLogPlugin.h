/*
        2025 10 01
*/

#pragma once

#include <stdio.h>

#include <vector>
#include <memory>
#include <mutex>
#include <thread>

#include "LoggerPlugin.h"
#include "socketcpp/UnixSocket.h"

namespace lkup69
{

class UnixSocketLogPlugin : public LoggerPlugin
{
        UnixSocketLogPlugin &operator=(const UnixSocketLogPlugin &) = delete;

        struct SocketConn {
                std::unique_ptr<UnixSocket> socketPtr;
                bool                        bConnected = false;
        };

private:
        UnixSocketLogPlugin(const std::string &addr);

public:
        ~UnixSocketLogPlugin() override;

public:
        static UnixSocketLogPlugin *CreatePluginIns(const std::string &addr = std::string{});

public:
        void operator()();

        void WriteLog(LEVEL_E level, const std::string &log) override;

private:
        std::string                 m_addr;
        std::vector<SocketConn>     m_socketConnVec;
        std::unique_ptr<UnixSocket> m_sockSrvPtr;
        bool                        m_bExit = false;
        std::mutex                  m_selfLock;
        std::thread                 m_worker;
};
}  // namespace lkup69
