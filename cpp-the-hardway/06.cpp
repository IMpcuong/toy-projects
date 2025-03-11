#include <cmath>
#include <iostream>

//
// Convenient IO functions.
//

template <typename... Args>
void print(const Args &...args)
{
  (std::cout << ... << args);
}

template <typename... Args>
void println(const Args &...args)
{
  (std::cout << ... << args) << "\n";
}

int main()
{
  int len = 100;
  auto still_square = [&]() mutable -> bool
  {
    len += 21;
    auto v = static_cast<int>(std::sqrt((float)len));
    return v * v == len;
  };
  if (still_square())
    println("YAYYY");

  println(std::log2(16.0));
  println(static_cast<int>(std::log2(16.0)));

  return 0;
}

