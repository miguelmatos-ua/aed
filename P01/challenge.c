#include <stdio.h>

typedef unsigned long u64;

void r(u64 n,int nd,int mask)
{
  if(nd == 10)
    printf("%lu\n",n);
  else
  {
    u64 nn = 10ul * n;
    for(int i = 0;i < 10;i++)
      if((mask & (1 << i)) == 0 && (nn + (u64)i) % (u64)(nd + 1) == 0ul)
        r(nn + (u64)i,nd + 1,mask | (1 << i));
  }
}

int main(void)
{
  r(0ul,0,0);
  return 0;
}
