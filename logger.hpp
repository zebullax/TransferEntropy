#ifndef LOGGER_HPP
#define LOGGER_HPP

#define LOGGERFILE "c:\temp\transferEntropy.log"
#include <cstring>
#include <fstream>

/*
	Logger implemented as a singleton.
	No check on file size, no roll over.
*/
class Logger{	
	
	public:
		enum LoggingLevel{
			ERROR,
			WARN,
			DEBUG
		}; //DEBUG < WARN < ERROR
		
		void SetLoggingLevel(LoggingLevel loggingLevel);
		void Warn(std::string message);		
		void Debug(std::string message);
		void Error(std::string message);
		void CheckFile();		
		static Logger* GetLogger();
	
	private:
		static Logger* _instance;
		std::ofstream _logFile;
		LoggingLevel _logLevel;
		
		Logger();	
		~Logger();		
		Logger(Logger const&);
		void operator=(Logger const&);	
};

#endif
