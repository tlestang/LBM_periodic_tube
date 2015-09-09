#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "stdio.h"

#include "allocate_lattice_arrays.h"
#include "initialize_lattice_arrays.h"
#include "equilibrium.h"
#include "streamCollCompute.h"
#include "boundaryConditions.h"
#include "write_vtk.h"

using namespace std;

int main()
{
  double ot = 1./3;
  double entry;
  /*Parameters for LB simulation*/
  double cs = 1./sqrt(3); double rho0 = 1.0;
  int q = 9; //Number of discrete directions
  int numberOfTimeSteps = 200000;
  int Dx=128, Dy=43; //Dimensions of grid
  int Lx = 10; int Ly = 10; //Dimensions of square
  double Ma = 0.03;   //Mach number
  double Re = 200;    //Reynolds number
  double tau = (Ma*Dy)/(cs*Re) + 0.5; //Relaxation time
  double nu = ot*(tau-0.5);
  double beta = -(8.0*rho0*cs*Ma*Ma*cs)/(Dy*Re);


  cout << "Simulation parameters" << endl;
  cout << "------------------------------------------" << endl;
  cout << "Re = " << Re << " --- Ma = " << Ma << endl;
  cout << "tau = " << tau << " --- beta = " << beta << endl;

  /*Populations and macroscopic fields*/
  double ***popHeapIn, ***popHeapOut, ***uFieldHeap, ***temp;
  double **rhoHeap;

  int dummy = 0, dummy2 = 0; int dummy3=0;


  /*Test if population file exists for this particular set of parameters*/
  stringstream filename; string yes = "yes"; string input;
  filename << "pop_"<<Re<<"_"<<Ma<<"_"<<Dx<<"_"<<Dy<<".datin";
  ifstream ifile;
  ifile.open(filename.str().c_str());
  if(ifile)
    {
      cout << "A population file for this particular set of parameters already exists. Do you wish to load the populations ? (yes/no)" << endl;
      cin >> input;
      if(input.compare(yes)){cout << "Launching corresponding Poiseuille flow simulation" << endl;}
      else
	{
	  cout << "Loading the populations" << endl;
	}
    }
  else
    {
      cout << "No population file exists yet for the particular set of parameters. Launching corresponding Poiseuille flow simulation" << endl;
    }


  cin >> entry;

  /* ---- | Allocate populations and fields | --- */

  popHeapIn = new double**[Dx]; popHeapOut = new double**[Dx];
  for (int i=0;i<Dx;i++)
    {
      popHeapIn[i] = new double*[Dy];
      popHeapOut[i] = new double*[Dy];
      for(int j=0;j<Dy;j++)
	{
	  popHeapOut[i][j] = new double[9];
	  popHeapIn[i][j] = new double[9];
	}
    }
  rhoHeap = new double*[Dx]; uFieldHeap = new double**[Dx];
  for(int i=0;i<Dx;i++)
    {
      rhoHeap[i] = new double[Dy];
      uFieldHeap[i] = new double*[Dy];
      for (int j=0;j<Dy;j++)
	{
	  uFieldHeap[i][j] = new double[2];
	}
    }
  

  



  /* START LBM PROCEDURE*/

  /*Initialization of population to equilibrium value*/
  initializePopulations(popHeapIn, Dx, Dy);
  initializeFields(rhoHeap, uFieldHeap, Dx, Dy);


  cout << "POISEUILLE" << endl;
  double uxSum; double uMean; double a; double seuil = 0.001;
  double u_ = 0; int t=0;
  fstream u_file("u_data.out", ios::out);
  /*FIRST STEP - POISEUILLE FLOW*/
  while(a>seuil)
    {
      if(t%(numberOfTimeSteps/100)==0){dummy3++; cout<<dummy3<<"%\r"; fflush(stdout);}
      /*Collision and streaming - Macroscopic fields*/
      streamingAndCollisionCompute(popHeapIn, popHeapOut, rhoHeap, uFieldHeap, Dx, Dy, q, tau);
            
      /* --- Boundary conditions --- */
      computeDomainCorners(popHeapOut, Dx, Dy);
      computeDomainNoSlipWalls(popHeapOut, Dx, Dy);
      computeDomainInletOutlet(popHeapOut, Dx, Dy, beta);
      /*Swap populations*/
      temp = popHeapIn;
      popHeapIn = popHeapOut;
      popHeapOut = temp;  


      /*Compute mean velocity along cylinder axis*/

      if(t%50==0 && t>0){
      uxSum=0.0;
      for(int x=0;x<Dx;x++){uxSum+=uFieldHeap[x][Dy/2][0];}
      uMean = uxSum/Dx;
      a = (uMean - u_)/uMean;
      u_ = uMean;

      t++;
      }
  
    }
  

  for (int lbTimeStepCount=0; lbTimeStepCount<numberOfTimeSteps;lbTimeStepCount++)
    {
      if(lbTimeStepCount%(numberOfTimeSteps/100)==0){dummy++; cout<<dummy<<"%\r"; fflush(stdout);}
      
      /*Collision and streaming - Macroscopic fields*/
      streamingAndCollisionCompute(popHeapIn, popHeapOut, rhoHeap, uFieldHeap, Dx, Dy, q, tau);
            
      /* --- Boundary conditions --- */
      computeDomainCorners(popHeapOut, Dx, Dy);
      computeDomainNoSlipWalls(popHeapOut, Dx, Dy);
      computeDomainInletOutlet(popHeapOut, Dx, Dy, beta);
      computeSquareBounceBack(popHeapOut, Dx, Dy, Lx, Ly);

      /*Write .vtk file
      if(lbTimeStepCount%(numberOfTimeSteps/1000)==0)
	{
	  dummy2++;
      write_fluid_vtk(dummy2, Dx, Dy, rhoHeap, uFieldHeap);
      }*/
      
          
	}
  
}




    
  

  
