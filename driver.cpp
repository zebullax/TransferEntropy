#include "transferEntropy.hpp"
#include <exception>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

double* MakeSampleData(int size, double (*makeNum)(double))
{
    double *result = new double [size];
    for (int i=0;i<size;i++)
    {
        result[i]=(*makeNum)((double)i);
    }
    return result;
}

double Identity (double n)
{
    return n;
}
double IncrementOne(double n)
{
    return n+1;
}

double DoubleIt(double n)
{
    return 2*n;
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
        series1 = MakeSampleData(SIZE,(&Identity));
        series2 = MakeSampleData(SIZE,(&DoubleIt));
        
        phaseSpace1 = PhaseSpaceReconstruction(series1,SIZE,DIM,LAG);
        phaseSpace2 = PhaseSpaceReconstruction(series2,SIZE,DIM,LAG);
        
        for (int i=0;i<nbElementsInResultVector;i++)
            for (int j=0;j<DIM;++j)
                assert(phaseSpace1[i][j]==series1[i+j*LAG]);
        OutputVectorToStream(cout,phaseSpace1,nbElementsInResultVector,DIM);
        OutputVectorToStream(cout,phaseSpace2,nbElementsInResultVector,DIM);
        
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
        series1 = MakeSampleData(SIZE,(&Identity));
        series2 = MakeSampleData(SIZE,(&IncrementOne));
        
        phaseSpace1 = PhaseSpaceReconstruction(series1,SIZE,DIM,LAG);
        phaseSpace2 = PhaseSpaceReconstruction(series2,SIZE,DIM,LAG);

        double te = TransferEntropy(phaseSpace1,phaseSpace2,nbElementsInResultVector,DIM,0.5);
        cout << "Transfer entropy = " << te <<endl;
        
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

void Test()
{
        //TestPhaseSpace();
    TestTransferEntropy();
}

int main(int argc, char**argv)
{
    Test();
}
