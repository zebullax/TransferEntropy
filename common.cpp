#include "common.hpp"
#include <string>

using namespace std;

string GetCurrentTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    
    strftime (buffer,80,"[%x %X ]\0",timeinfo);
    string result(buffer);
    return result;
}
