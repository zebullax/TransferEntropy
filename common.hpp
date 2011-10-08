#ifndef COMMON_HPP
#define COMMON_HPP

#include <ctime>
#include <string>
using namespace std;

//This function takes 2 vectors and tell us the distance between us
typedef double (*Distance) (double* X,double* Y,int embeddingDimension);
//Will tell us if a set of distances are found to be close enough to infer vectors are same.
typedef bool (*Norm) (double* dist, int nbDist, double threshold);

string GetCurrentTime();

#endif
