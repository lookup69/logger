/*
        2024-10-08
*/

#include "UnixSocketLogPlugin.h"

#include <signal.h>
#include <sys/epoll.h>

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

        m_sockSrvPtr.reset(UnixSocket::CreateSocket(SOCK_STREAM));
}

UnixSocketLogPlugin::~UnixSocketLogPlugin()
{
        m_sockSrvPtr->Close();
        m_bExit = true;

        if (m_worker.joinable())
                m_worker.join();
}

UnixSocketLogPlugin *UnixSocketLogPlugin::CreatePluginIns(const std::string &addr)
{
        UnixSocketLogPlugin *plugin = new (std::nothrow) UnixSocketLogPlugin{ addr };

        if (plugin and (plugin->m_sockSrvPtr != nullptr)) {
                plugin->m_worker = std::thread{ std::ref(*plugin) };

        } else {
                delete plugin;

                return nullptr;
        }

        return plugin;
}

void UnixSocketLogPlugin::operator()()
{
        int epoll_fd;

        auto epollAddWatch__ = [&epoll_fd](int fd) -> int {
                struct epoll_event event = { 0 };

                event.data.fd = fd;
                event.events  = EPOLLIN;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, event.data.fd, &event) == -1)
                        return -1;

                return 0;
        };

        epoll_fd = epoll_create1(EPOLL_CLOEXEC);
        if (epoll_fd == -1)
                return;

        if (epollAddWatch__(m_sockSrvPtr->GetSocket()) == -1)
                return;

        if (m_sockSrvPtr->Bind(m_addr) == -1)
                return;

        if (m_sockSrvPtr->Listen(1) == -1)
                return;

        while (!m_bExit) {
                struct epoll_event events[1] = { 0 };
                int                nfds;
                SocketConn         sc;

                nfds = epoll_wait(epoll_fd, events, sizeof(events) / sizeof(struct epoll_event), 100);
                for (int i = 0; i < nfds; ++i) {
                        printf("xx1.........................\n");
                        if ((events[i].data.fd == m_sockSrvPtr->GetSocket()) and (events[i].events == EPOLLIN)) {
                                sc.socketPtr.reset(m_sockSrvPtr->Accept());

                                printf("xx2.........................\n");

                                if (sc.socketPtr.get() != nullptr) {
                                        const std::lock_guard<std::mutex> lock(m_selfLock);

                                        sc.bConnected = true;
                                        m_socketConnVec.emplace_back(std::move(sc));
                                }
                        }
                }
        }
}

void UnixSocketLogPlugin::WriteLog(LEVEL_E level, const std::string &log)
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
