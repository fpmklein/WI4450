#include "gtest_mpi.hpp"

#include "operations.hpp"

#include "cg_solver.hpp"

#include <iostream>

#include <cmath>

#include <limits>


TEST(cg_example, identity)
{
  const int nx=2, ny=2, nz=2;
  const int n = nx * ny * nz;
  double *x = new double[n];
  double *b = new double[n];
  double tol = std::sqrt(std::numeric_limits<double>::epsilon());
  int maxIter = n;
  double resNorm;
  int numIter;

  stencil3d S;
  S.nx = nx; S.ny = ny; S.nz = nz;
  S.value_c = 1;
  S.value_n = 0;
  S.value_e = 0;
  S.value_s = 0;
  S.value_w = 0;
  S.value_b = 0;
  S.value_t = 0;

  init(n, x, 1.0); init(n, b, 2.0); cg_solver(&S, n, x, b, tol, maxIter, &resNorm, &numIter);
  if (numIter < maxIter)
    EXPECT_NEAR(0.0, resNorm, tol);
  else
    std::cout<<"Reached maximum number of iterations"<<std::endl;
  std::cout<<"matrix3d is a idenity matrix and b is a vector with all elements equal to 2"<<std::endl;
  std::cout<<"cg value for x, "<< "true value for x"<<std::endl;
  for (int i=0; i<n; i++) std::cout<<x[i]<<", 2 "<<std::endl;

  delete [] x;
  delete [] b;
}

TEST(cg_example, stencil)
{
  const int nx=2, ny=2, nz=2;
  const int n = nx * ny * nz;
  double *x = new double[n];
  double *b = new double[n];
  double tol = std::sqrt(std::numeric_limits<double>::epsilon());
  int maxIter = n;
  double resNorm;
  int numIter;

  stencil3d S;
  S.nx = nx; S.ny = ny; S.nz = nz;
  S.value_c = 8;
  S.value_n = 2;
  S.value_e = 4;
  S.value_s = 2;
  S.value_w = 4;
  S.value_b = 1;
  S.value_t = 1;

  init(n, x, 1.0);
  init(n, b, 0.0);
  cg_solver(&S, n, x, b, tol, maxIter, &resNorm, &numIter);
  if (numIter < maxIter)
    EXPECT_NEAR(0.0, resNorm, tol);
  else
    std::cout<<"Reached maximum number of iterations"<<std::endl;

  delete [] x;
  delete [] b;
}
