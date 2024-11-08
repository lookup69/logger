
/*
        2024-10-08
*/

#include <thread>

#include "logger.h"
#include "ConsoleLogPlugin.h"
#include "UnixSocketLogPlugin.h"
#include "FileLogPlugin.h"

// g++ -std=c++17 -o logger -I.. main.cpp ../logger.cpp ../ConsoleLogPlugin.cpp  ../UnixSocketLogPlugin.cpp ../FileLogPlugin.cpp ../socketcpp/UnixSocket.cpp -pthread
int main()
{
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::ConsoleLogPlugin>(lkup69::ConsoleLogPlugin::CreatePluginIns()), "consolePlugin");
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::UnixSocketLogPlugin>(lkup69::UnixSocketLogPlugin::CreatePluginIns()), "socketPlugin");
        lkup69::Logger::RegisterLogPlugin(std::unique_ptr<lkup69::FileLogPlugin>(lkup69::FileLogPlugin::CreatePluginIns("/tmp/aaa/aaa.log", 20)), "filePlugin");

        printf("pid:%u\n", getpid());

        for (int i = 0; i < 5; ++i) {
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
                log_info("time: %d", i);
                if(i % 2)
                        enable_plugin("consolePlugin");
                else    
                        disable_plugin("consolePlugin");

                log_err_f("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                log_warn_f("cccccccccccccccccccccccccc\n");
                log_trace_f("%d %d %s\n", 10, 20, "xxxxxxxx");
                log_info_f("%d %d %s\n", 10, 20, "xxxxxxxx");
                log_normal_f("%d  uuuuuuu\n", i);
                log_normal_f("xxxxxxxxxxxxxxxxxxxxxxx\n");

                log_err("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                log_warn("cccccccccccccccccccccccccc\n");
                log_trace("%d %d %s\n", 10, 20, "xxxxxxxx");
                log_info("%d %d %s\n", 10, 20, "xxxxxxxx");
                log_normal("%d  uuuuuuu\n", i);
                log_normal("xxxxxxxxxxxxxxxxxxxxxxx\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));

        }

        return 0;
}
