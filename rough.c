/**CHECK THE LIMITS AND VALUES BEFORE USING**/
//Making the coefficient matrix
  for(i=0;i<num_x-1;i++)
    for(j=0;j<num_x-1;j++)
      M[i*(num_x+2)+j] = 0;
  for(i=0;i<num_x;i++)
      M[i*(num_x+2)+i] = 2*(1+lambda);
  for(i=0;i<num_x-1;i++)
      M[i*(num_x+2) + i+1] = -lambda;
  for(i=0;i<num_x-1;i++)
      M[(i+1)*(num_x+2)+i] = -lambda;
