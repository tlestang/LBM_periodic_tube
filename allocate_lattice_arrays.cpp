  void allocate_pops(double*** fin, double*** fout, int Dx, int Dy)
  {
    fin = new double**[Dx]; fout = new double**[Dx];
    for (int i=0;i<Dx;i++)
	     {
	       fin[i] = new double*[Dy];
	       fout[i] = new double*[Dy];
	       for(int j=0;j<Dy;j++)
		 {
		   fout[i][j] = new double[9];
		   fin[i][j] = new double[9];
		 }
	     }
  }
void allocate_fields(double** rho, double*** u, int Dx, int Dy)
  {
    rho = new double*[Dx]; u = new double**[Dx];
    for(int i=0;i<Dx;i++)
      {
	rho[i] = new double[Dy];
	u[i] = new double*[Dy];
	for (int j=0;j<Dy;j++)
	  {
	    u[i][j] = new double[2];
	  }
      }
  }
