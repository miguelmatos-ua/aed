//
// Tomás Oliveira e Silva, AED, September 2014, September 2017
//
// example of function overloading (same function name, different argument numbers and/or data types)
//

#include <iostream>

using std::cout; // make this symbol from the std namespace directly visible

void show(const int i)
{
  cout << "int: "
       << i
       << std::endl;
}

void show(const double d)
{
  cout << "double: "
       << d
       << std::endl;
}

void show(const char *s,const char *h = "string: ") // second argument with default value
{
  cout << h
       << s
       << std::endl;
}

//char
void show(const char c)
{
  cout << "char: "
       << c
       << std::endl;
}

//array of 3 integers
void show(const int i[3]) {
  cout << "array: "
       << "[" << i[0] << "," << i[1] << "," << i[2] << "]"
       << std::endl;
}

int main(void)
{
  show(1.0);
  show("hello");
  show(-3);
  show("John","name: ");
  show('a');
  int a[3] = {2, 7, -1};
  show(a);
  return 0;
}
