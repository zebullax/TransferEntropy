#ifndef transferEntropyHPP
#define transferEntropyHPP

#include <iostream>
#include "common.hpp"

double** PhaseSpaceReconstruction(double* timeSeries,int timsSeriesSize,int embeddingDimension,int timeDelay);
double euclideanDistance (double* X, double* Y,int dim);
bool maxNorm(double* dist,int n, double threshold);
double tripleProbaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold);
double doubleProbaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold);
double TransferEntropy(double** X, double** Y, int length,int dimension,double threshold);

#endif
