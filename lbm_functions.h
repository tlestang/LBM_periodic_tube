double fEquilibrium(int k, double rho, double *u)
{
  /* Lattice Constants*/
  double w[9]={4.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0};
  int c[9][2] = {{0,0}, {1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {-1,-1}, {1,-1}};
  /* --- */
  double eu = c[k][0]*u[0] + c[k][1]*u[1];
  double u2 = u[0]*u[0] + u[1]*u[1];
  double A = 3.0*eu;
  double B = 4.5*eu*eu;
  double C = -1.5*u2;

  return w[k]*rho*(1.0+A+B+C);
}
