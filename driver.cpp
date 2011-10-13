#include "transferEntropy.hpp"
#include "dataFile.hpp"
#include <exception>
#include <iostream>
#include <cassert>

using namespace std;

double* MakeSampleData(int size, double (*makeNum) (double,int) ,int mode)
{
    double *result = new double [size];
    for (int i=0;i<size;i++)
    {
        result[i]=(*makeNum)((double)i ,mode);
    }
    return result;
}

double MakeNum(double n , int mode)
{
    switch (mode){
            case 0:
                return n;
            case 1:
                return n+0.001;
            case 2:
                return 2*n;
            default:
                return 0;
        }
}

void TestPhaseSpace()
{
    const int SIZE = 10;
    const int DIM = 3;
    const int LAG = 2;
            
    double *series1 = NULL;
    double **phaseSpace1=NULL;
    double *series2 = NULL;
    double **phaseSpace2=NULL;
    try{
        int nbElementsInResultVector = SIZE-(LAG*(DIM-1)); 
        series1 = MakeSampleData(SIZE,(&MakeNum),0);
        series2 = MakeSampleData(SIZE,(&MakeNum),2);
        
        phaseSpace1 = PhaseSpaceReconstruction(series1,SIZE,DIM,LAG);
        phaseSpace2 = PhaseSpaceReconstruction(series2,SIZE,DIM,LAG);
        
        for (int i=0;i<nbElementsInResultVector;i++)
            for (int j=0;j<DIM;++j)
                assert(phaseSpace1[i][j]==series1[i+j*LAG]);
        OutputVectorSeriesToStream(cout,phaseSpace1,nbElementsInResultVector,DIM);
        OutputVectorSeriesToStream(cout,phaseSpace2,nbElementsInResultVector,DIM);
        
            //CLean up
        delete series1;
        delete series2;
        series1 = NULL;
        series2 = NULL;
	
        for (int i=0;i<nbElementsInResultVector;++i)
        {
            delete[] phaseSpace1[i];
            delete[] phaseSpace2[i];
        }
        delete phaseSpace1;
        delete phaseSpace2;
    }
    catch(std::exception& ex)
    {
        int nbElementsInResultVector = SIZE-(LAG*(DIM-1)); 
        if (series1 != NULL)
            delete series1;
        if (series2 != NULL)
            delete series2;
        
        if (phaseSpace1 != NULL)
        {                    
            for (int i=0;i<nbElementsInResultVector;++i)
            {
                delete[] phaseSpace1[i];
            }
            delete []phaseSpace1;
        }
        if (phaseSpace2 != NULL)
        {                    
            for (int i=0;i<nbElementsInResultVector;++i)
            {
                delete[] phaseSpace2[i];
            }
            delete []phaseSpace2;
        }                
        throw;
    }
}

void TestTransferEntropy()
{
    const int SIZE = 10;
    const int DIM = 3;
    const int LAG = 2;
            
    double *series1 = NULL;
    double **phaseSpace1=NULL;
    double *series2 = NULL;
    double **phaseSpace2=NULL;
    try{
        int nbElementsInResultVector = SIZE-(LAG*(DIM-1)); 
        series1 = MakeSampleData(SIZE,(&MakeNum),0);
        series2 = MakeSampleData(SIZE,(&MakeNum),1);
        
        phaseSpace1 = PhaseSpaceReconstruction(series1,SIZE,DIM,LAG);
        phaseSpace2 = PhaseSpaceReconstruction(series2,SIZE,DIM,LAG);

        double te = TransferEntropy(phaseSpace1,phaseSpace2,nbElementsInResultVector,DIM,2);
        cout << "RESULT : Transfer entropy = " << te <<endl;
        
            //CLean up
        delete series1;
        delete series2;
        series1 = NULL;
        series2 = NULL;
	
        for (int i=0;i<nbElementsInResultVector;++i)
        {
            delete[] phaseSpace1[i];
            delete[] phaseSpace2[i];
        }
        delete phaseSpace1;
        delete phaseSpace2;
    }
    catch(std::exception& ex)
    {
        int nbElementsInResultVector = SIZE-(LAG*(DIM-1)); 
        if (series1 != NULL)
            delete series1;
        if (series2 != NULL)
            delete series2;
        
        if (phaseSpace1 != NULL)
        {                    
            for (int i=0;i<nbElementsInResultVector;++i)
            {
                delete[] phaseSpace1[i];
            }
            delete []phaseSpace1;
        }
        if (phaseSpace2 != NULL)
        {                    
            for (int i=0;i<nbElementsInResultVector;++i)
            {
                delete[] phaseSpace2[i];
            }
            delete []phaseSpace2;
        }                
        throw;
    }
}

void TestTentMap()
{
    const int LENGTH = 100;
    const int TRANSIENT = 10000;
    const int RUN = 100;
    const double COUPLING = 0.05;
    
    double* X=NULL;
    double* Y=NULL;
    
    MakeTentMapSeries(TRANSIENT,RUN,LENGTH,COUPLING,X,Y);
    if (X!=NULL)
        OutputVectorToStream(cout,X,RUN);
    if (Y!=NULL)
        OutputVectorToStream(cout,Y,RUN);
    
        //OutputVectorSeriesToStream(cout,result,LENGTH,RUN);        
}

void TestReadCSV(string fileName)
{
    int length;
    
    double* X = ReadFileOfDoubles(fileName,';',0,length);
    double* Y = ReadFileOfDoubles(fileName,';',1,length);

    if (X!=NULL)
        OutputVectorToStream(cout,X,length);
    if (Y!=NULL)
        OutputVectorToStream(cout,Y,length);

    delete X;
    delete Y;
        
}

void Test()
{
        //TestPhaseSpace();
        //TestTransferEntropy();
    TestTentMap();
    string fileName = "dataseries.csv";
    TestReadCSV(fileName);
        
}

int main(int argc, char**argv)
{
    Test();
}
