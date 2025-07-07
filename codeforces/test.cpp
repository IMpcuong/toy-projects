#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string STH = "evaporate";

std::string get_nonsense()
{
  return STH;
}

void print_ref_nonsense(std::string &&s)
{
  std::cout << s << "\n";
}

void print_ref_nonsense(const std::string &s)
{
  std::cout << s << "\n";
}

void add_l(int &&x, int &&y)
{
  int *x_ptr = &x;
  int *y_ptr = &y;
  std::cout << x << " " << x_ptr << "\n";
  std::cout << y << " " << y_ptr<< "\n";
  std::cout << x + y << "\n";
}

int main()
{
  int x = 10;
  int y = 100;
  add_l(y - x, x * 2);

  // int dx = 2 * x; // @Note: dx := lvalue.
  // add_l(dx, dx);

  add_l(5, 10);

  std::string obstinate_pilfer = "obstinate---pilfer";
  print_ref_nonsense(obstinate_pilfer);
  print_ref_nonsense(get_nonsense());

  std::cout << 1 / 6 << "\n";
  std::cout << 2 % 6 << "\n";

  std::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = std::vector(a.begin(), a.begin() + 2);

  namespace ranges = std::ranges;
  ranges::for_each(b, [](const auto &n) -> void { std::cout << n << " "; });

  char sth = static_cast<char>(std::toupper(static_cast<unsigned char>('a')));
  std::cout << sth << "\n";

  std::cout << 'a' - 'A' << "\n";

  std::string s = "in the name of love";
  std::cout << s.substr(2) << "\n";
}
