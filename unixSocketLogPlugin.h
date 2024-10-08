#pragma once

#include <stdio.h>
#include <signal.h>

#include <vector>
#include <memory>

#include "LoggerPlugin.h"
#include "socketcpp/UnixSocket.h"

namespace lkup69
{

class UnixSocketLogPlugin : public LoggerPlugin
{
        UnixSocketLogPlugin &operator=(const UnixSocketLogPlugin &) = delete;

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
                        std::unique_ptr<UnixSocket> socketPtr;

                        socketPtr.reset(m_sockSrv->Accept());

                        if (socketPtr.get() != nullptr)
                                m_writeSocketVec.emplace_back(std::move(socketPtr));
                }
        }

private:
        std::string                              m_addr;
        std::vector<std::unique_ptr<UnixSocket>> m_writeSocketVec;
        std::unique_ptr<UnixSocket>              m_sockSrv;
        bool                                     m_bExit = false;
};
}  // namespace lkup69
