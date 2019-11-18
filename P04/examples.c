//
// Tomás Oliveira e Silva, AED, October 2014, October 2018
//
// empirical computational complexity (the first function is already fully done)
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


static long int counter; // counts the number of loop iterations

////////////////////////////////////////////////////////////////////////////////
// O(n) algorithms
////////////////////////////////////////////////////////////////////////////////

double vector_sum(int n,
                  double a[n])
{
  double r;
  int i;

  r = a[0];
  for(i = 1;i < n;i++)
  {
    counter++; // count the number of loop iterations
    r += a[i];
  }
  return r;
}

double vector_inner_product(int n,
                            double a[n],
                            double b[n])
{
  double r;
  int i;

  r = a[0] * b[0];
  for(i = 1;i < n;i++)
    r += a[i] * b[i];
  return r;
}

void vector_addition(int n,
                     double a[n],
                     double b[n],
                     double r[n])
{ // r = a + b
  int i;

  for(i = 0;i < n;i++)
    r[i] = a[i] + b[i];
}

double factorial(int n)
{
  return (n < 2) ? 1.0 : n * factorial(n - 1);
}

////////////////////////////////////////////////////////////////////////////////
// O(n^2) algorithms (here, ^ means exponentiation)
////////////////////////////////////////////////////////////////////////////////

double matrix_sum(int n,
                  double A[n][n])
{
  double r;
  int i,j;

  r = 0.0;
  for(i = 0;i < n;i++)
    for(j = 0;j < n;j++)
      r += A[i][j];
  return r;
}

void matrix_vector_product(int n,
                           double A[n][n],
                           double b[n],
                           double r[n])
{ // r = A * b
  int i,j;

  for(i = 0;i < n;i++)
  {
    r[i] = 0.0;
    for(j = 0;j < n;j++)
      r[i] += A[i][j] * b[j];
  }
}

void matrix_addition(int n,
                     double A[n][n],
                     double B[n][n],
                     double R[n][n])
{ // R = A + B
  int i,j;

  for(i = 0;i < n;i++)
    for(j = 0;j < n;j++)
      R[i][j] = A[i][j] + B[i][j];
}

void insertion_sort(int n,
                    double a[n])
{
  double d;
  int i,j;

  for(i = 1;i < n;i++)
  {
    d = a[i];
    for(j = i;j > 0 && d < a[j - 1];j--)
      a[j] = a[j - 1];
    a[j] = d;
  }
}


////////////////////////////////////////////////////////////////////////////////
// O(n^3) algorithms (here, ^ means exponentiation)
////////////////////////////////////////////////////////////////////////////////

void matrix_matrix_product(int n,
                           double A[n][n],
                           double B[n][n],
                           double R[n][n])
{ // R = A * B
  int i,j,k;

  for(i = 0;i < n;i++)
    for(j = 0;j < n;j++)
      R[i][j] = 0.0;
  for(i = 0;i < n;i++)
    for(j = 0;j < n;j++)
      for(k = 0;k < n;k++)
        R[i][j] += A[i][k] * B[k][j];
}

double matrix_determinant(int n,
                          double A[n][n])
{ // A is modified
  double r,t;
  int i,j,k;

  r = 1.0;
  for(i = 0;i < n;i++)
  {
    // find the biggest element (the pivot)
    j = i;
    for(k = i + 1;k < n;k++)
      if(fabs(A[k][i]) > fabs(A[j][i]))
        j = k;
    // exchange lines (if necessary)
    if(j != i)
      for(r = -r,k = i;k < n;k++)
      {
        t = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = t;
      }
    // Gauss-Jordan elimination
    for(r *= A[i][i],j = i + 1;j < n;j++)
      for(k = i + 1;k < n;k++)
        A[j][k] -= (A[j][i] / A[i][i]) * A[i][k];
  }
  return r;
}


////////////////////////////////////////////////////////////////////////////////
// algorithms with exponential complexity
////////////////////////////////////////////////////////////////////////////////

double F(int n)
{
  return (n < 2) ? (double)n : F(n - 1) + F(n - 2);
}

double Fi(int n)
{
  static double Ft[10] = { 0,1,1,2,3,5,8,13,21,34 };

  return (n < 10) ? Ft[n] : Fi(n - 1) + Fi(n - 2);
}

void print_all_sums(int n,double a[n])
{ // 1 <= n <= 30
  int i,j,mask;
  double s;

  if(n < 1 || n > 30)
    return;
  mask = 0; // a bit set to 0 means that the
            // corresponding a[i] will not
            // contribute to the sum
  do
  {
    // do sum
    s = 0.0;
    for(i = j = 0;i < n;i++)
      if(((mask >> i) & 1) != 0)
      {
        s += a[i];
        printf("%sa[%d]",(j == 0) ? "" : "+",i);
        j = 1; // next time print a + sign
      }
    printf("%s = %.3f\n",(j == 0) ? "empty" : "",s);
    // next subset (discrete binary counter)
    mask++;
  }
  while(mask < (1 << n));
}


////////////////////////////////////////////////////////////////////////////////
// algorithm with factorial complexity
////////////////////////////////////////////////////////////////////////////////

void print_all_permutations(int n,int m,int a[])  // int a[] is a synonym of int *a
{
  int i;

  if(m < n - 1)
  { // not yet at the end
    for(i = m;i < n;i++)
    {
#define swap(i,j)  do { int t = a[i]; a[i] = a[j]; a[j] = t; } while(0)
      swap(i,m);                         // exchange a[i] with a[m]
      print_all_permutations(n,m + 1,a); // recurse
      swap(i,m);                         // undo the exchange of a[i] with a[m]
#undef swap
    }
  }
  else
  { // visit permutation
    for(i = 0;i < n;i++)
      printf("%s%d",(i == 0) ? "" : " ",a[i]);
    printf("\n");
  }
}


////////////////////////////////////////////////////////////////////////////////
// algorithms with small complexity
////////////////////////////////////////////////////////////////////////////////

double power_dd(double x,double y)
{
  return exp(y * log(x));
}

double power_di(double x,int n)
{
  double t;

  if(n < 0)
    return power_di(1.0 / x,-n);
  if(n == 0)
    return 1.0;
  t = power_di(x * x,n / 2);       // the integer division discards a fractional part
  return (n % 2 == 0) ? t : x * t; // take care of the discarded fractional part
}


////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv)
{
  int i,n;

  if(argc != 2)
  {
    fprintf(stderr,"usage: %s case_number\n",argv[0]);
     return 1;
  }
  switch(atoi(argv[1])) // convert the first (and only) argument to an integer
  {
    case 1:
      printf("data for the O(n) functions\n");
      printf("\n");
      printf(" n vector_sum vector_inner_product vector_addition factorial\n");
      printf("-- ---------- -------------------- --------------- ---------\n");
      for(n = 1;n <= 20;n++)
      {
        double a[n];

        for(i = 0;i < n;i++)
          a[i] = (double)rand() / (double)RAND_MAX; // an uniformly distributed pseudo-random number
        printf("%2d",n);
        counter = 0l;
        (void)vector_sum(n,a); // ignore the return value!
        printf(" %10ld",counter);
        //
        // place your code here
        //
        printf("\n");
      }
      printf("-- ---------- -------------------- --------------- ---------\n");
      break;
    //
    // do the other cases here
    //
  }
  return 0;
}
