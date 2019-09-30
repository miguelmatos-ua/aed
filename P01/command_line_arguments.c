//
// Tomás Oliveira e Silva, AED, September 2019
//
// list the command line arguments
//

#include <stdio.h>

int main(int argc,char *argv[argc])
{
  for(int i = 0;i < argc;i++)
    printf("argv[%d] = \"%s\"\n",i,argv[i]);
  return 0;
}
