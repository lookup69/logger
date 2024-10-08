
/*
*/

#include <thread>

#include "logger.h"
#include "ConsoleLogPlugin.h"
#include "UnixSocketLogPlugin.h"
#include "FileLogPlugin.h"

// g++ -std=c++17 -o logger logger.cpp ConsoleLogPlugin.cpp main.cpp unixSocketLogPlugin.cpp FileLogPlugin.cpp socketcpp/UnixSocket.cpp -pthread
int main()
{
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::ConsoleLogPlugin>(lkup69::ConsoleLogPlugin::CreatePluginIns()));
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::UnixSocketLogPlugin>(lkup69::UnixSocketLogPlugin::CreatePluginIns()));
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::FileLogPlugin>(lkup69::FileLogPlugin::CreatePluginIns("/tmp/aaa/aaa.log", 20)));

        printf("pid:%u\n", getpid());

        int i = 0;
        while (1) {
                ++i;
#if 0                
                lkup69::Logger::Log("[%s][%s][%d]%s", __FILE__, __PRETTY_FUNCTION__, __LINE__, "aaa");
                lkup69::Logger::Info("[%s][%s][%d]%s", __FILE__, __PRETTY_FUNCTION__, __LINE__, "aaa");
                lkup69::Logger::Warn("[%s][%s][%d]%s", __FILE__, __PRETTY_FUNCTION__, __LINE__, "aaa");
                lkup69::Logger::Err("[%s][%s][%d]%s", __FILE__, __PRETTY_FUNCTION__, __LINE__, "aaa");

                lkup69::Logger::Log("bbb");
                lkup69::Logger::Info(100000 + i);
                lkup69::Logger::Warn(1.0001);
                lkup69::Logger::Err("cccccccccccccccc");
#endif                
                log_err("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                log_info("%d %d %s\n", 10, 20, "xxxxxxxx");
                log_warn("cccccccccccccccccccccccccc\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        return 0;
}
