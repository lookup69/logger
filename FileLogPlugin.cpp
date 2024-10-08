/*
        2024-05-24
*/

#include "FileLogPlugin.h"

#include <fstream>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
error "Missing the <filesystem> header."
#endif

using namespace lkup69;

FileLogPlugin::FileLogPlugin(const std::string &file, size_t maxLines)
        : m_file(file),
          m_maxLines(maxLines)
{
        size_t pos;

        pos = file.rfind('/');
        if (pos != std::string::npos) {
                std::string path = file.substr(0, pos);

                if (fs::exists(path) == false)
                        fs::create_directories(path);
        }

        if (fs::exists(m_file)) {
                std::ifstream logfile(m_file);

                if (logfile.is_open()) {
                        std::string line;

                        while (std::getline(logfile, line))
                                if (!line.empty()) {
                                        if (line.at(line.size() - 1) != '\n')
                                                line.push_back('\n');
                                        m_logVec.push_back(line);
                                }
                }
        }
}

// static
FileLogPlugin *FileLogPlugin::CreatePluginIns(const std::string &file, size_t maxLines)
{
        return new (std::nothrow) FileLogPlugin{ file, maxLines };
}

void FileLogPlugin::WriteLog(int level, const std::string &log)
{
        auto               now        = std::chrono::system_clock::now();
        std::time_t        now_c      = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
        std::tm           *local_time = std::localtime(&now_c);
        std::ostringstream oss;
        std::string        line;
        std::ofstream      logfile(m_file, std::ofstream::trunc);

        oss << "[" << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "]";

        line.append(oss.str());
        line.append(log);

        if (line.at(line.size() - 1) != '\n')
                line.push_back('\n');

        if (m_logVec.size() > m_maxLines)
                m_logVec.erase(m_logVec.begin());

        m_logVec.emplace_back(line);

        if (logfile.is_open()) {
                for (const auto &log : m_logVec)
                        logfile << log;
        }
}