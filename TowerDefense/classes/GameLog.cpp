#include "GameLog.h"

// Singleton Yeah!
GameLog GameLog::m_GameLog;

void GameLog::Init(std::ostream &os, const std::string &caller, int log_level)
{
     m_sLogCaller = "unknown";
     m_iLogLevel = log_level;
     LogStream = &os;
}

void GameLog::Log(const std::string &msg, int log_level = 5)
{
    if(m_iLogLevel >= log_level)
    {
        *LogStream << m_sLogCaller << ": " << msg << std::endl;
    }
}

void GameLog::LogError(const std::string &msg)
{
    std::string error = "Error: ";
    error.append(msg); // put Error in front of our message
    Log(error, 3);
}

void GameLog::LogSdlError(const std::string &function_name)
{
    std::string sdl_error = SDL_GetError();

    sdl_error.append(function_name + ": ");

    LogError(sdl_error);
}

void GameLog::SetCaller(std::string &caller)
{
    m_sLogCaller = caller;
}

void GameLog::SetLogLevel(int log_level)
{
    m_iLogLevel = log_level;
}

std::string GameLog::GetCaller()
{
    return m_sLogCaller;
}

int GameLog::GetLogLevel()
{
    return m_iLogLevel;
}
