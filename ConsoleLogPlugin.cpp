/*
        2024-05-24
*/

#include "ConsoleLogPlugin.h"

#include <cstdio>
#include <map>

using namespace lkup69;

/**
#define NONE            "\033[m"
#define RED             "\033[0;32;31m"
#define LIGHT_RED       "\033[1;31m"
#define GREEN           "\033[0;32;32m"
#define LIGHT_GREEN     "\033[1;32m"
#define BLUE            "\033[0;32;34m"
#define LIGHT_BLUE      "\033[1;34m"
#define DARY_GRAY       "\033[1;30m"
#define CYAN            "\033[0;36m"
#define LIGHT_CYAN      "\033[1;36m"
#define PURPLE          "\033[0;35m"
#define LIGHT_PURPLE    "\033[1;35m"
#define BROWN           "\033[0;33m"
#define YELLOW          "\033[1;33m"
#define LIGHT_GRAY      "\033[0;37m"
#define WHITE           "\033[1;37m"
*/

static std::map<LEVEL_E, const std::string> sColorMap = {
        { LEVEL_E::INFO,   "\033[1;33m" }, // YELLOW
        { LEVEL_E::TRACE,  "\033[1;32m" }, // LIGHT_GREEN
        { LEVEL_E::WARN,   "\033[1;34m" }, // LIGHT_BLUE
        { LEVEL_E::ERR,    "\033[1;31m" }, // LIGHT_RED
        { LEVEL_E::NORMAL, "\033[m"     }  // NORMAL
};

void ConsoleLogPlugin::WriteLog(LEVEL_E level, const std::string &log)
{
        if (level != LEVEL_E::NORMAL)
                fprintf(stderr, "%s", sColorMap[level].c_str());

        fprintf(stderr, "%s", log.c_str());

        if (level != LEVEL_E::NORMAL)
                fprintf(stderr, "%s", sColorMap[LEVEL_E::NORMAL].c_str());
}
