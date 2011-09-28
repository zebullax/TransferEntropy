#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "logger.hpp"

using namespace std;

Logger* Logger::_instance = NULL;

void Logger::SetLoggingLevel(LoggingLevel loggingLevel)
{
	_logLevel=loggingLevel;
}		
void Logger::Warn(string message)
{
	CheckFile();
	if(_logLevel==ERROR)
		return;
	_logFile << "[WARN]" << message;
}

void Logger::Debug(string message)
{
	CheckFile();
	if(_logLevel!=DEBUG)
		return;
	_logFile << "[DEBUG]" << message;
}

void Logger::Error(string message)
{
	CheckFile();
	_logFile << "[ERROR]" << message;
}

void Logger::CheckFile()
{
	if(_logFile==NULL || !_logFile.is_open())
	{
		_logFile.open(LOGGERFILE,ios::out);
	}
}		

Logger* Logger::GetLogger()
{
	if (Logger::_instance == NULL)
		Logger::_instance = new Logger;
	return Logger::_instance;		
}

Logger::Logger()
{
	_logFile.open(LOGGERFILE,ios::out);
	_logLevel = DEBUG;
}	

Logger::~Logger()
{
	_logFile.close();
}
