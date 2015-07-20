#include <iostream>
#include <cmath>

int main()
{
  /*Parameters for LB simulation*/
  double cs = 1./sqrt(3);
  int q = 9; //Number of discrete directions
  int numberOfTimeSteps = 1000;
  int Dx=128, Dy=128; //Dimensions of grid

  double Ma = 0.01;   //Mach number
  double Re = 100;    //Reynolds number
  double tau = 0.5 + (Ma*D)/(Re*cs); //Relaxation time

  /*Populations and macroscopic fields*/
  double ***popHeapIn, ***popHeapOut, ***uFieldHeap;
  double **rhoHeap;

  /*Allocate memory for populations and fields*/
  allocate_pops(popHeapIn, popHeapOut, Dx, Dy);
  allocate_fields(rhoHeap, uFieldHeap, Dx, Dy);

  /* START LBM PROCEDURE*/

  /*Initialization of population to equilibrium value*/
  initializePopulations(fin, Dx, Dy, q);
  initializeFields(rho, u, Dx, Dy);



  /*LOOP OF LB TIMESTEPS*/

  for (int lbTimeStepCount=0; lbTimeStepCount<numberOfTimeSteps;lbTimeStepCount++)

    {

    }
}


    
  

  
