#include "transferEntropy.hpp"
#include "logger.hpp"
#include <exception>

double* MakeSampleData(int size)
{
	double *result = new double [size];
	for (int i=0;i<size;i++)
	{
		result[i]=(double)i;
	}
	return result;
}

void TestPhaseSpace()
{
	double *series = NULL;
	double **phaseSpace=NULL;
	try{
		series = MakeSampleData(200);
		int nbElementsInResultVector = 200-(2*(5-1)); 
		phaseSpace = PhaseSpaceReconstruction(series,200,5,2);	
		delete series;	
		series = NULL;
		
		for (int i=0;i<nbElementsInResultVector;++i)
		{
			delete[] phaseSpace[i];
		}
		delete phaseSpace;
	}
	catch(std::exception& ex)
	{
		int nbElementsInResultVector = 200-(2*(5-1)); 
		if (series != NULL)
			delete series;
		for (int i=0;i<nbElementsInResultVector;++i)
		{
			delete[] phaseSpace[i];
		}
		delete []phaseSpace;
		throw;
	}
}

void RunTest()
{
	TestPhaseSpace();
}

int main(int argc, char**argv)
{
    RunTest();	
}
