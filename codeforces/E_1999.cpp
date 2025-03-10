#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

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

// ----- //

const int UPPER_BOUND = 2 * 1e5;

int exact_log_with_base(long num, int base)
{
  return std::log2(num) / std::log2(base);
}

auto precomputed_log_values = [](const long &range,
                                 const int &base = 3) -> std::vector<long>
{
  std::vector<long> needed_steps;
  needed_steps.reserve(range);
  for (long num = 1; num <= range; num++)
  {
    int v = exact_log_with_base(num, base);
    needed_steps.emplace_back(v + 1 /* 1 more step to reach 0 */);
  }
  return needed_steps;
}(UPPER_BOUND);

auto precomputed_list_sum_of_log = [](const std::vector<long> &computed_logs)
    -> std::vector<long>
{
  std::vector<long> list_sum_of_log;
  list_sum_of_log.reserve(computed_logs.size());
  int sum_val = 0;
  for (const auto &computed_log : computed_logs)
  {
    sum_val += computed_log;
    list_sum_of_log.emplace_back(sum_val);
  }
  return list_sum_of_log;
}(precomputed_log_values);

int solve()
{
  unsigned long long l, r;
  std::cin >> l >> r;

  int smaller_sum = precomputed_list_sum_of_log[l - 1];
  int greater_sum = precomputed_list_sum_of_log[r - 1];
  return (greater_sum - smaller_sum) + precomputed_log_values[l - 1] * 2;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // auto test_log_vec = std::vector<int>(precomputed_log_values.begin(),
  //                                      precomputed_log_values.begin() + 100);
  // for (auto &v : test_log_vec)
  //   println(v);

  // auto test_sum_vec = std::vector<int>(precomputed_list_sum_of_log.begin(),
  //                                      precomputed_list_sum_of_log.begin() + 10);
  // for (auto &v : test_sum_vec)
  //   println(v);

  int T = 1;
  std::cin >> T;
  for (int i = 0; i < T; i++)
    println(solve());

  return 0;
}
