/*
        2024-05-24
*/

#include "ConsoleLogPlugin.h"

#include <cstdio>

using namespace lkup69;

static const char *COLOR[] = {
        "\033[1;33m",  // INFO : YELLOW
        "\033[1;34m",  // WARN : LIGHT_BLUE
        "\033[1;31m",  // ERR  : LIGHT_RED
        "\033[m",      // NOMARL
        nullptr
};

void ConsoleLogPlugin::WriteLog(int level, const std::string &log)
{
        if (level != LEVEL_E::NOMARL)
                fprintf(stderr, "%s", COLOR[level]);

        fprintf(stderr, "%s", log.c_str());
        if (log.at(log.size() - 1) != '\n')
                fprintf(stderr, "\n");

        if (level != LEVEL_E::NOMARL)
                fprintf(stderr, "%s", COLOR[LEVEL_E::NOMARL]);
}
