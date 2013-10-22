#include "GameLog.h"

void GameLog::Init(std::ostream &os, const std::string &caller, int log_level) 
{
     LogCaller = caller;
     CurrentLogLevel = log_level;
     LogStream = &os;
}

void GameLog::Log(const std::string &msg, int log_level)
{
    if( ! log_level )
    {
        log_level = 5;
    }
    if(CurrentLogLevel >= log_level)
    {
        *LogStream << LogCaller << ": " << msg << std::endl;
    }
}

void GameLog::LogError(const std::string &msg)
{
    std::string error = "Error ";
    error.append(msg); // put Error in front of our message
    Log(error, 3);
}
