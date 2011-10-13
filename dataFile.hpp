#ifndef DATAFILE_HPP
#define DATAFILE_HPP

#include <string>

double* ReadFileOfDoubles(std::string filename,const char delimiter,int nbOfLinesToJump,int& length);
void MakeTentMapSeries(int nbOfIterToDiscard , int nbOfIterToKeep, int latticeLength , double couplingStrength ,double*& serieA,double*& serieB);

#endif
