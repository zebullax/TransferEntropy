#include <cmath>
#include <sstream>
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
                // result[i][...] ith vector
            result[i][j] = timeSeries[i+j*timeDelay];
        }
    }
    
#ifdef _DEBUG
    cout <<GetCurrentTime()<< " PhaseSpaceReconstruction: Initial series with length " << timeSeriesSize <<" has been reconstructed with dimension " << embeddingDimension<< " and has now " << nbElementsInResultVector <<" elements"<<endl;
#endif
    
    return result;
}

double EuclideanDistance (double* X, double* Y,int dim)
{
#ifdef _DEBUG
    cout<<GetCurrentTime()<<"EuclideanDistance [enter]"<<endl;
#endif
    
    double tmp=0;
    for (int i=0;i<dim;++i)
    {
        
#ifdef _DEBUG
        ostringstream msgToLog;        
        msgToLog << GetCurrentTime()<<"X_i"<< X[i]<< "Y_i" << Y[i];
        cout<<msgToLog.str()<<endl;

#endif        
        tmp+=pow(X[i]-Y[i],2);
    }
    
#ifdef _DEBUG
    ostringstream msg;    
    msg << GetCurrentTime()<<"Distance = Sqrt("<< tmp<<")";
    cout<<msg.str()<<endl;
    cout<<GetCurrentTime()<<"EuclideanDistance [exit]"<<endl;
#endif
    
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

#ifdef _DEBUG
    cout<<GetCurrentTime()<<"ProbaEstimation [ENTER]"<<endl;
#endif
    
    for (int i=0;i<length-1;++i)
    {
        if (i!=n)
        {
            distances[0] = distance(X[n+1],X[i+1],dimension);
            distances[1] = distance(X[n],X[i],dimension);
            distances[2] = distance(Y[n],Y[i],dimension);
            
#ifdef _DEBUG
                //May be replaced by StringStream
            ostringstream msg;            
            msg <<GetCurrentTime()<<"ProbaEstimation Distances:" << distances[0] <<  " , " << distances[1]<< " , " <<distances[2];
            cout<<msg.str()<<endl;
#endif
            proba+=norm(distances,3,threshold);
        }
        
    }
    proba = proba/(double(length)-1);
    assert (proba>=0);
    assert (proba<=1);
#ifdef _DEBUG
    cout<<GetCurrentTime()<<"ProbaEstimation [EXIT]"<<endl;
#endif
    return proba;
}

double TransferEntropy(double** X, double** Y, int length,int dimension,double threshold)
{
    double result =0;
        
    for(int i=0;i<length-1;++i)
    {
        double proba = ProbaEstimation(X,Y,length,i,dimension,EuclideanDistance,MaxNorm,threshold);
        result+=proba;
        
#ifdef _DEBUG
        ostringstream msg;
        msg << GetCurrentTime()<<"Transfer entropy, proba at step "<<i<<" : "<< proba<< " current transfer entropy :" <<result;
        cout<<msg.str()<<endl;
#endif
        
    }

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
