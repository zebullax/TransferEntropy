#ifndef LOGGER_HPP
#define LOGGER_HPP

#define LOGGERFILE "transferEntropy.log"
#include <cstring>
#include <fstream>

/*
  Logger implemented as a singleton.
  > No check on file size, no roll over.
  > Mandat call to Release is dangerous -> Call for a redesign
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
    void Release();
    
    static Logger* GetLogger();
    static Logger* GetDebugLogger();
    
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
