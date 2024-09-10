#include <cmath>
#include <iostream>

int main()
{
  float res_1 = std::abs(-10000.0f);
  std::cout << res_1 << std::endl;

  float res_2 = std::fabs(-10000.0f);
  std::cout << res_2 << std::endl;

  return 0;
}