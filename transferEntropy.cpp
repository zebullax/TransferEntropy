#include <cmath>
#include <iostream>
#include <assert.h>
#include "transferEntropy.hpp"

using namespace std;

/*
This will build a vector space from a time series, using time delay technique
reconstructing the phase space.

Ex: with embedding dimension 4 and timeDelay 2:

0 1 2 3 4 5 6 7 8 9

become:

0 1 2 3
2 3 4 5
3 4 5 6
4 6 7 8
*/
double** PhaseSpaceReconstruction(double* timeSeries,int timeSeriesSize,int embeddingDimension,int timeDelay)
{
  int nbElementsInResultVector = timeSeriesSize-(timeDelay*(embeddingDimension-1));
  double** result = NULL;
      
  result = new double* [nbElementsInResultVector];
  for (int i=0; i<nbElementsInResultVector;++i)
  {
	  for (int j=0;j<embeddingDimension;++j)
	  {
		if (j==0)
			result[i]=new double[embeddingDimension];
		result[i][j] = timeSeries[i+j*timeDelay];
		}
	}
  return NULL;
}

double EuclideanDistance (double* X, double* Y,int dim)
{  
  double tmp=0;
  for (int i=0;i<dim;++i)
    {
      tmp+=pow(X[i]-Y[i],2);
    }
  return sqrt(tmp);  
}

bool MaxNorm(double* dist,int n, double threshold)
{
  double max = dist[0];
  for (int i=1;i<n;++i)
    {
      if (dist[i]>max)
	max=dist[i];
    }
  
  return (max <= threshold);
}

/*
Eq: 4.5

compute P(xn+1,xn,yn)
length and dimension are supposed to be the same for X and Y.
*/
double probaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold)
{
  double proba = 0;
  double* distances = new double[3];
  
  for (int i=0;i<length-1;++i)
    {
      distances[0] = distance(X[i+1],X[i+1],dimension);
      distances[1] = distance(X[i],X[i],dimension);
      distances[2] = distance(Y[i],Y[i],dimension);
      
      proba+=norm(distances,3,threshold);
    }
  proba = proba/(double(length)-1);
  assert (proba >0);
  assert (proba<1);
  return proba;
}

double TransferEntropy(double** X, double** Y, int length,int dimension,double threshold)
{
  double result =0;
  
  for(int i=0;i<length-1;++i)
    {
      double proba = probaEstimation(X,Y,length,i,dimension,EuclideanDistance,MaxNorm,threshold);
      result+=proba;
    }
  return result;
}

void OutputVectorToStream(ostream& target,double** X, int length,int dimension)
{
	for (int i=0 ; i<length ; ++i)
	{
		for(int j=0;j<dimension;++j)
		{
			target<<X[i*dimension+j]<<";";
		}
	target<<endl;
	}
}
