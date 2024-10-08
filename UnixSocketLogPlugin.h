#pragma once

#include <stdio.h>
#include <signal.h>

#include <vector>
#include <memory>
#include <mutex>

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
        ~UnixSocketLogPlugin() override
        {
                m_bExit = true;
        }

public:
        static UnixSocketLogPlugin *CreatePluginIns(const std::string &addr = std::string{});

public:
        void WriteLog(int level, const std::string &log) override;

        void operator()()
        {
                if (m_sockSrv->Bind(m_addr) == -1) {
                }

                if (m_sockSrv->Listen(1) == -1) {
                }

                while (!m_bExit) {
                        SocketConn sc;

                        sc.socketPtr.reset(m_sockSrv->Accept());

                        if (sc.socketPtr.get() != nullptr) {
                                const std::lock_guard<std::mutex> lock(m_selfLock);

                                sc.bConnected = true;
                                m_socketConnVec.emplace_back(std::move(sc));
                        }
                }
        }

private:
        std::string                 m_addr;
        std::vector<SocketConn>     m_socketConnVec;
        std::unique_ptr<UnixSocket> m_sockSrv;
        bool                        m_bExit = false;
        std::mutex                  m_selfLock;
};
}  // namespace lkup69
