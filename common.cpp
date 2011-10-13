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
    
    strftime (buffer,80,"[%x %X] \0",timeinfo);
    string result(buffer);
    return result;
}

void OutputVectorSeriesToStream(ostream& target,double** X, int length,int dimension)
{
    for (int i=0 ; i<length ; ++i)
    {
        OutputVectorToStream(target,X[i],dimension);
    }
}

void OutputVectorToStream(ostream& target,double* X, int dimension)
{
    for(int j=0;j<dimension;++j)
    {
        target<<X[j]<<";";
    }
    target<<endl;
}
