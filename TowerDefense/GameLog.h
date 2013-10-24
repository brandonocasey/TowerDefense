#ifndef GAMELOG_H
#define GAMELOG_H

#include <ostream>
#include <string>
#include <iostream>

class GameLog
{
    private:
        std::ostream* LogStream;
        int CurrentLogLevel;
        std::string LogCaller;
    public:
        void Init(std::ostream &os, const std::string &caller, int log_level = 5);
        void Log(const std::string &msg, int log_level = 5);
        void LogError(const std::string &msg);
        // void getLogger(); for singleton
};

#endif