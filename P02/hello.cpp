/*
** Tomás Oliveira e Silva, AED, September 2014
**
** my first C++ program (compare with hello.c)
*/

#include <iostream>

int main(void)
{
  std::cout << "Hello world!\n";
  for (int i =1; i <= 10 ; i++)
    if (i==10)
      std::cout << i << '\n';
    else
      std::cout << i << ',';
  // return 0;  NOTE that in C++ main() returns 0 if no return value is given
}
