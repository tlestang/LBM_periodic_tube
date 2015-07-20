  void allocate_pops(double***, double***, int, int)
  {
    fin = new double**[Dx]; fout = new double**[Dx];
    for int(i=0;i<Dx;i++)
	     {
	       fin[i] = new double*[Dy];
	       fout[i] = new double*[Dy];
	       for(int j=0;j<Dy;j++)
		 {
		   fout[i][j] = new double[q];
		   fin[i][j] = new double[q];
		 }
	     }
  }
  void allocate_fields(double***, double***, int, int, int)
  {
    rho = new double*[Dx]; u = new double**[Dx];
    for(int i=0;i<Dx;i++)
      {
	rho[i] = new double*[Dy];
	u[i] = new double*[Dy];
	for (int j=0;j<Dy;j++)
	  {
	    u[i][j] = new double[2];
	  }
      }
  }
