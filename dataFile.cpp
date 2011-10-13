#ifndef DATAFILE_HPP
#define DATAFILE_HPP

#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <exception>

#include "dataFile.hpp"
#include "common.hpp"

using namespace std;

//Read a single-line from a csv-file
double* ReadFileOfDoubles(string filename,const char delimiter,int nbOfLinesToJump, int& length)
{
    try{        
        char *line = NULL;
        
            //Open file
        ifstream dataFile(filename.c_str());
        if (!dataFile.is_open()) 
            return 0;
    
            //Read the line from file and copy it to buffer
        string readLine;
        getline(dataFile,readLine);
            //skip some lines if needed (ugly...)
        for (int i=0;i<nbOfLinesToJump;++i)
            getline(dataFile,readLine);
        line = new char[readLine.size()];
        readLine.copy(line,readLine.size(),0);
    
        vector<double> vec;
        char *resultOfTok = strtok(line,&delimiter);
        while(resultOfTok != NULL)
        {
            vec.push_back(atof(resultOfTok));
            resultOfTok = strtok(line,&delimiter);
        }
        length = vec.size();
        
            //Convert it to an array
        return &vec[0];
    }
    catch(exception& ex)
    {
        return NULL;
    }
    
}

/*
 *Return in serieA and serieB a spatiotemporal serie based on some iterations of a tent map
 */
void MakeTentMapSeries(int iterToDiscard , int iterToKeep, int length , double coupling,double*& serieA,double*& serieB)
{
    serieA = new double[iterToKeep];
    serieB = new double[iterToKeep];
    double *lattice = NULL;
    
    try{

        lattice =  new double [length];
        for (int j=0; j<length;++j)
        {
            lattice[j]=max(0.001,(((double)rand())/RAND_MAX));
        }
        
        for (int i=0; i<iterToDiscard+iterToKeep;++i)
        {
                //old value will keep the value being overwritten used by neighbor for update
            double oldValue = lattice[length-1];
            
            for (int j=0;j<length;++j)
            {
                double x =0;
                x = coupling*oldValue+(1-coupling)*lattice[j];
                if (x<0.5)
                    x = x*2;
                else
                    x = 2-2*x;
                oldValue = lattice[j];
                lattice[j]=x;            
            }
            
            if(i>=iterToDiscard)
            {
                serieA[i-iterToDiscard]=lattice[(int)(length/2)];
                serieB[i-iterToDiscard]=lattice[(int)(length/2)+1];
            }            
        }
        
    }
    catch(std::exception& ex)
    {
        if (lattice!=NULL){
            delete lattice;
            lattice=NULL;
        }
        
        if (serieA!=NULL){
            delete serieA;
            serieA=NULL;
        }
        
        if(serieB!=NULL){
            delete serieB;
            serieB=NULL;
        }
        cout << ex.what();
        
        throw;
    }
}

#endif
