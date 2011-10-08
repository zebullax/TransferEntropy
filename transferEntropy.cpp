#include <cmath>
#include <iostream>
#include <assert.h>
#include "logger.hpp"
#include "transferEntropy.hpp"

using namespace std;
/*
 * ifdef around logging is to prevent perf grieving on useless string building
 * */

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
                // result[i][...] ith vector
            result[i][j] = timeSeries[i+j*timeDelay];
        }
    }
    
#ifdef _DEBUG
    Logger* log = Logger::GetDebugLogger();
    string msg;
    msg = "PhaseSpaceReconstruction: Initial series with length ";
    msg += timeSeriesSize;
    msg+="  has been reconstructed with dimension ";
    msg+= embeddingDimension;
    msg+=" and now has ";
    msg+=nbElementsInResultVector;
    msg+=" elements.";

    log->Debug(msg);
    log->Release();
#endif
    
    return result;
}

double EuclideanDistance (double* X, double* Y,int dim)
{
    Logger* log = Logger::GetDebugLogger();
    log->Debug("EuclideanDistance [enter]");
    double tmp=0;
    for (int i=0;i<dim;++i)
    {
        
#ifdef _DEBUG
        string msgToLog;
        
        msgToLog += "X_i";
        msgToLog += X[i];
        msgToLog += "Y_i";
        msgToLog += Y[i];
        log->Debug(msgToLog);

#endif        
        tmp+=pow(X[i]-Y[i],2);
    }
    
#ifdef _DEBUG
    string msgToLog;    
    msgToLog = "Distance = Sqrt(";
    msgToLog+=tmp;
    msgToLog +=")";
    log->Debug(msgToLog);
#endif
    
    log->Debug("EuclideanDistance [exit]");
    log->Release();
    
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
double ProbaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold)
{
    double proba = 0;
    double* distances = new double[3];
    Logger* log = Logger::GetDebugLogger();
    log->Debug("ProbaEstimation [ENTER]");
    
    for (int i=0;i<length-1;++i)
    {
        if (i!=n)
        {
            distances[0] = distance(X[n+1],X[i+1],dimension);
            distances[1] = distance(X[n],X[i],dimension);
            distances[2] = distance(Y[n],Y[i],dimension);
            
#ifdef _DEBUG
                //May be replaced by StringStream
            string msgToLog;
            
            msgToLog = "ProbaEstimation Distances:";
            msgToLog += distances[0];
            msgToLog += " , ";
            msgToLog += distances[1];
            msgToLog += " , ";
            msgToLog += distances[2];
            
            log->Debug(msgToLog);
#endif
            proba+=norm(distances,3,threshold);
        }
        
    }
    proba = proba/(double(length)-1);
    assert (proba>=0);
    assert (proba<=1);

    log->Debug("ProbaEstimation [EXIT]");
    log->Release();

    return proba;
}

double TransferEntropy(double** X, double** Y, int length,int dimension,double threshold)
{
    double result =0;
    Logger* log = Logger::GetDebugLogger();    
        
    for(int i=0;i<length-1;++i)
    {
        double proba = ProbaEstimation(X,Y,length,i,dimension,EuclideanDistance,MaxNorm,threshold);
        result+=proba;
        cout <<length<<endl;
        
#ifdef _DEBUG
        string msg;
        msg = "Transfer entropy, proba at step : ";
        msg+= i;
        msg+=proba;
        msg+= " current transfer entropy :";
        msg+=result;
        log->Debug(msg);
        
#endif
        
    }
    log->Release();
    return result;
}

void OutputVectorToStream(ostream& target,double** X, int length,int dimension)
{
    for (int i=0 ; i<length ; ++i)
    {
        for(int j=0;j<dimension;++j)
        {
            target<<X[i][j]<<";";
        }
	target<<endl;
    }
}
