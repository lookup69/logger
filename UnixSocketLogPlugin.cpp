#include "UnixSocketLogPlugin.h"

#include <thread>

using namespace lkup69;

UnixSocketLogPlugin::UnixSocketLogPlugin(const std::string &addr)
        : m_addr(addr)
{
        // prevent SIGPIPE, Broken pipe
        signal(SIGPIPE, SIG_IGN);

        if (m_addr.empty()) {
                m_addr = "/tmp/.";
                m_addr += std::to_string(getpid()) + std::string{ ".logger" };
        }

        m_sockSrv.reset(UnixSocket::CreateSocket(SOCK_STREAM));
}

UnixSocketLogPlugin *UnixSocketLogPlugin::CreatePluginIns(const std::string &addr)
{
        UnixSocketLogPlugin *plugin = new (std::nothrow) UnixSocketLogPlugin{ addr };

        if (plugin) {
                std::thread worker(std::ref(*plugin));

                worker.detach();
        }

        return plugin;
}

void UnixSocketLogPlugin::WriteLog(int level, const std::string &log)
{
        const std::lock_guard<std::mutex> lock(m_selfLock);

        for (std::vector<SocketConn>::iterator it = m_socketConnVec.begin(); it != m_socketConnVec.end(); ++it) {
                if (it->socketPtr->Write(log.c_str(), log.size()) < 0)
                        it->bConnected = false;
        }

        // TODO
        // Enhance remove disconnect socket
        // for (auto &it : m_socketConnVec) {
        //        printf("socket:%d   bConnected:%s\n", it.socketPtr->GetSocket(), (it.bConnected) ? "true" : "false");
        //}
        std::vector<SocketConn>::iterator it = m_socketConnVec.begin();
        while (it != m_socketConnVec.end()) {
                if (it->bConnected == false) {
                        m_socketConnVec.erase(it);
                        return;
                }
                ++it;
        }
}
