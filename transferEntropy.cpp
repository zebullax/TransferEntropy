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
    OutputVectorSeriesToStream(cout,result,nbElementsInResultVector,embeddingDimension);    
#endif
    
    return result;
}

double EuclideanDistance (double* X, double* Y,int dim)
{
    double tmp=0;
    double distance = 0;

#ifdef _DEBUG
        ostringstream msgToLog;
        msgToLog << GetCurrentTime();
        msgToLog<<"EuclideanDistance between those 2 vectors";        
        cout<<msgToLog.str()<<endl;
        cout<<GetCurrentTime();
        OutputVectorToStream(cout,X,dim);
        cout<<GetCurrentTime();
        OutputVectorToStream(cout,Y,dim);
#endif        
    
    for (int i=0;i<dim;++i)
        tmp+=pow(X[i]-Y[i],2);
    distance = sqrt(tmp);
    
#ifdef _DEBUG
    ostringstream msg;    
    msg << GetCurrentTime()<<"Distance = "<<distance;
    cout<<msg.str()<<endl;
#endif
    
    return distance;  
}

bool MaxNorm(double* dist,int n, double threshold)
{
  double max = dist[0];
  for (int i=1;i<n;++i)
    {
      if (dist[i]>max)
	max=dist[i];
    }
#ifdef _DEBUG
  ostringstream msg;    
  if (max<threshold)
      msg<<"Found an equal point, max value was "<<max;
  else
      msg<<"max value "<< max<<" was over the threshold "<<threshold;
  cout<<msg<<endl;
#endif    
  return (max <= threshold);
}

/*
 *TODO
 *Double and Triple proba estimation can be factorized
 **/
double TripleProbaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold)
{
    double proba = 0;
    double* distances = new double[3];

    for (int i=0;i<length-1;++i)
    {
        if (i!=n)
        {
            distances[0] = distance(X[n+1],X[i+1],dimension);
            distances[1] = distance(X[n],X[i],dimension);
            distances[2] = distance(Y[n],Y[i],dimension);
            
#ifdef _DEBUG
            ostringstream msg;            
            msg <<GetCurrentTime()<<"TripleProbaEstimation - Distances(Xi+1,Xi,Yi) :" << distances[0] <<  " , " << distances[1]<< " , " <<distances[2];
            cout<<msg.str()<<endl;
#endif
            proba+=norm(distances,3,threshold);
        }
        
    }
    proba = proba/(double(length)-1);
    assert (proba>=0);
    assert (proba<=1);

    delete distances;    
    return proba;
}

double DoubleProbaEstimation(double** X, double** Y,int length, int n, int dimension,Distance distance,Norm norm,double threshold)
{
    double proba = 0;
    double* distances = new double[2];
    
    for (int i=0;i<length-1;++i)
    {
        if (i!=n)
        {
            distances[0] = distance(X[n+1],X[i+1],dimension);
            distances[1] = distance(X[n],X[i],dimension);
            
#ifdef _DEBUG
            ostringstream msg;            
            msg <<GetCurrentTime()<<"DoubleProbaEstimation - Distances(Xi+1,Xi) :" << distances[0] <<  " , " << distances[1];
            cout<<msg.str()<<endl;
#endif
            proba+=norm(distances,2,threshold);
        }        
    }
    proba = proba/(double(length)-1);
    assert (proba>=0);
    assert (proba<=1);

    delete distances;    
    return proba;
}

// TODO : Phase Space Reconstruction should be embedded in here... So the cleanup should also occur here.
double TransferEntropy(double** X, double** Y, int length,int dimension,double threshold)
{
    double result =0;
    for(int i=0;i<length-1;++i)
    {
        double tripleProba = TripleProbaEstimation(X,Y,length,i,dimension,EuclideanDistance,MaxNorm,threshold);
        double doubleProba = DoubleProbaEstimation(X,Y,length,i,dimension,EuclideanDistance,MaxNorm,threshold);
        result+=tripleProba*log(tripleProba/doubleProba);        
        
#ifdef _DEBUG
        ostringstream msg;
        msg << GetCurrentTime()<<"Transfer entropy, step "<<i<<" : triple proba="<< tripleProba<< " double proba="<<doubleProba<<" , current transfer entropy=" <<result;
        cout<<msg.str()<<endl;
#endif
        
    }
    return result;
}
