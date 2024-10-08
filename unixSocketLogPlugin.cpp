#include "unixSocketLogPlugin.h"

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
        for (std::vector<std::unique_ptr<UnixSocket>>::iterator it = m_writeSocketVec.begin(); it != m_writeSocketVec.end(); ++it) {
                if (it->get()->GetSocket() != -1) {
                        if (it->get()->Write(log.c_str(), log.size()) < 0) {
                                m_writeSocketVec.erase(it);
                        }
                }
        }
}
