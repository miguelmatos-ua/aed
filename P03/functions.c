//
// Tomás Oliveira e Silva, AED, September 2014, September 2015
//
// the functions for the first exercise of class P.03
// (for a given positive value of n, find a formula for the return value of each function)
//

#include <stdio.h>

int f1(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += 1;
  return r;
}

int f2(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += 1;
  return r;
}

int f3(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= n;j++)
      r += 1;
  return r;
}

int f4(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += i;
  return r;
}

int f5(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = i;j <= n;j++)
      r += 1;
  return r;
}

int f6(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += j;
  return r;
}

int main(void)
{
  // place your code here
  printf("f1: %d\n",f1(10));
  printf("f2: %d\n",f2(10));
  printf("f3: %d\n",f3(10));
  printf("f4: %d\n",f4(10));
  printf("f5: %d\n",f5(10));
  printf("f6: %d\n",f6(10));
}
