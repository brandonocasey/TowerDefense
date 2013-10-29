#include "GameLog.h"

// Singleton Yeah!
GameLog GameLog::m_GameLog;

GameLog* GameLog::Init(std::ostream &os, std::string &caller, int log_level)
{
     m_GameLog.SetCaller(caller);
     m_GameLog.SetLogLevel(log_level);
     m_GameLog.SetLogFile(os);

     return &m_GameLog;
}

void GameLog::Log(const std::string &msg, int log_level)
{
    if(m_iLogLevel >= log_level)
    {
        *m_cLogFile << m_sLogCaller << ": " << msg << std::endl;
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

void GameLog::SetLogFile( std::ostream &os )
{
    m_cLogFile = &os;
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
