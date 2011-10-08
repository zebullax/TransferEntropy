#ifndef DATAFILE_HPP
#define DATAFILE_HPP

#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "dataFile.hpp"

using namespace std;

//Read a single-line csv-file
double* ReadFileOfDoubles(string filename,const char *delimiter)
{
	char *line = NULL;
		
	//Open file
	ifstream dataFile(filename.c_str());
	if (!dataFile.is_open()) 
		return 0;
	
	//Read the line from file and copy it to buffer
	string readLine;
	getline(dataFile,readLine);
	line = new char[readLine.size()];
	readLine.copy(line,readLine.size(),0);

	vector<double> vec;
	char *resultOfTok = strtok(line,delimiter);
    while(resultOfTok != resultOfTok)
    {
		vec.push_back(atof(resultOfTok));
		resultOfTok = strtok(line,delimiter);
    }    
    //Convert it to an array
    return &vec[0];
}

#endif
