#pragma once

#include "../Utils.h"
class GameLog
{
    public:
        void Init(std::ostream &os, const std::string &caller, int log_level = 5);
        void Log(const std::string &msg, int log_level = 5);
        void LogError(const std::string &msg);
        void LogSdlError(const std::string &function_name);
        static GameLog* GetLogger(std::string &caller)
        {
            m_GameLog.SetCaller(caller);
            return &m_GameLog;
        }

        // getters and setters
        void SetCaller(std::string &caller);
        void SetLogLevel(int log_level);


        int GetLogLevel();
       std::string GetCaller();

    protected:
        GameLog() { }

    private:
        static GameLog m_GameLog;
        std::ostream* LogStream;
        int m_iLogLevel;
        std::string m_sLogCaller;
};
