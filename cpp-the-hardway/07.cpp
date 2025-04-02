#include <algorithm>
#include <concepts> // Required for standard (comparable, etc) concepts.
#include <iostream>
#include <iterator>
#include <type_traits> // For type traits, void_t.
#include <utility>     // For declval, forward.
#include <vector>

using namespace std;

//
// @Note:
//  + https://pvs-studio.com/en/blog/posts/cpp/1149/
//  + https://dice-research.org/news/2022-03-25_cpp_perfect_forwarding/#:~:text=Reference%20Collapsing&Also%20only%20the%20inner%20qualifiers,outer%20ones%20will%20be%20ignored.
//

int main()
{
  vector<long> v(2);
  v[0] = 1;
  v[1] = 5;
  v.emplace_back(100);
  for_each(v.cbegin(), v.cend(), [](long n)
           { cout << n << " "; });
  copy(v.cbegin(), v.cend(), ostream_iterator<long>(cout, " "));

  int num = -11;
  cout << num % 1007 << "\n";

  // @Note: C++20.
  auto is_neg_num = [](auto &&num) -> bool
  {
    if constexpr (requires { num < 0; })
    {
      return num < 0;
    }
  };

  vector<int> a = {-1, -2, 0, 10, 13, 53, 90};
  int neg_cnt1 = ranges::count_if(a, is_neg_num);
  cout << neg_cnt1 << "\n";

  // @Note: C++17.
  auto is_neg_num_alt = [](auto &&num) -> bool
  {
    using TypeX = decay_t<decltype(num)>;
    using TypeZ = decay_t<decltype(0)>;
    if constexpr (totally_ordered<TypeX> && same_as<TypeX, TypeZ>)
    {
      return num < 0;
    }
  };

  vector<int> b = {1, 2, 3, 4, 5};
  int neg_cnt2 = ranges::count_if(b, is_neg_num_alt);
  cout << neg_cnt2 << "\n";

  return 0;
}
