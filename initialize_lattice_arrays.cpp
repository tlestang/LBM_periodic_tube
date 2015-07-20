#include "lbm_functions.h"

void initializePopulations(double ***fin, int Dx, int Dy, int q)
{
  double rho0 = 1.0; double zeroVelocity[2] = {0.0, 0.0};
  for(int x=0;x<Dx;x++)
    {
      for(int y=0;y<Dy;y++)
	{
	  for(int k=0;k<9;k++)
	    {
	      fin[x][y][k] = fEquilibrium(k, rho0, zeroVelocity);
	    }
	}
    }
}

void initializeFields(double **rho, double ***u, int Dx, int Dy, int q)
{
  double rho0 = 1.0; double zeroVelocity[2] = {0.0, 0.0};
  for(int x=0;x<Dx;x++)
    {
      for(int y=0;y<Dy;y++)
	{
	  rho[x][y] = rho0;
	  u[x][y][0] = zeroVelocity[0];
	  u[x][y][1] = zeroVelocity[1];
      	}
    }
}
