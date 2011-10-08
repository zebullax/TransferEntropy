#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "logger.hpp"

using namespace std;

Logger* Logger::_instance = NULL;

void Logger::SetLoggingLevel(LoggingLevel loggingLevel)
{
    cout<<"SetLoggingLevel"<<endl;
    
   _logLevel=loggingLevel;
}

string GetCurrentTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    
    strftime (buffer,80,"%x %X \0",timeinfo);
    string result(buffer);
    return result;
    
}

void Logger::Warn(string message)
{
    CheckFile();
    if(_logLevel==ERROR)
        return;
    _logFile << "[WARN]" << GetCurrentTime() <<" : "<<message <<"\n";
}

void Logger::Debug(string message)
{
#ifdef _DEBUG
    cout << "Call logger::debug"<<endl;
    
    CheckFile();
    if(_logLevel!=DEBUG)
        return;
    _logFile << "[DEBUG]" << GetCurrentTime() <<" : "<<message <<"\n";
#endif
}

void Logger::Error(string message)
{
    CheckFile();
    if(_logLevel!=DEBUG)
        return;
    _logFile << "[ERROR]" << GetCurrentTime() <<" : "<<message <<"\n";
}

void Logger::CheckFile()
{
    if(_logFile==NULL || !_logFile.is_open())
    {
        cout<<"CheckFile : File was not open..."<<endl;        
        _logFile.open(LOGGERFILE,ios_base::ate);
    }
}		

Logger* Logger::GetLogger()
{
    if (Logger::_instance == NULL)
    {
        cout<<"Creation de l instance"<<endl;
        Logger::_instance = new Logger;
    }    
    return Logger::_instance;		
}

Logger* Logger::GetDebugLogger()
{
    Logger* instance = GetLogger();
    instance->SetLoggingLevel(DEBUG);
    return instance;
}

Logger::Logger()
{
    _logFile.open(LOGGERFILE,ios_base::ate);
    _logLevel = DEBUG;
}

Logger::~Logger()
{
    _logFile.close();
}

void Logger::Release()
{
    _logFile.close();
}
