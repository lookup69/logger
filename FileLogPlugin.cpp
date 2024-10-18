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

void FileLogPlugin::WriteLog(LEVEL_E level, const std::string &log)
{
        std::ofstream      logfile(m_file, std::ofstream::trunc);

        if (m_logVec.size() > m_maxLines)
                m_logVec.erase(m_logVec.begin());

        m_logVec.emplace_back(log);

        if (logfile.is_open()) {
                for (const auto &m : m_logVec)
                        logfile << m;
        }
}