#include <math.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>

// clang++ -std=c++20 -O2 04.cpp -o out 2> out.log

#define FLUSH_STDOUT_OF(m, k, v) \
  std::cout                      \
      << m.size() << " | "       \
      << k << " : " << v         \
      << "\n";

struct SolarSystem
{
  std::string star_name;

  friend bool operator==(const SolarSystem &first, const SolarSystem &second)
  {
    return first.star_name == second.star_name;
  }

  friend std::ostream &operator<<(std::ostream &os, const SolarSystem &star)
  {
    os << star.star_name;
    return os;
  }
};

template <>
struct std::hash<SolarSystem>
{
  size_t operator()(const SolarSystem &s) const noexcept
  {
    return std::hash<std::string>{}(s.star_name);
  }
};

int main()
{
  std::unordered_map<int, std::string> status_codes{
      {200, "Success"},
      {404, "This is not the page you're looking for"},
  };
  auto iter = status_codes.find(200);
  if (iter != status_codes.end())
    std::cout << iter->first << ": " << iter->second << "\n";

  std::string void_msg = status_codes[500];
  status_codes[502] = "Bad gateway";
  for (auto const &[k, v] : status_codes)
    FLUSH_STDOUT_OF(status_codes, k, v);

  for (auto const &item : status_codes)
    FLUSH_STDOUT_OF(status_codes, item.first, item.second);

  std::unordered_map<int, std::string>::iterator m_iter;
  for (m_iter = status_codes.begin(); m_iter != status_codes.end(); m_iter++)
    FLUSH_STDOUT_OF(status_codes, m_iter->first, m_iter->second);

  std::unordered_set<std::string> planets{
      "Venus",
      "Jupiter",
      "Mars",
  };
  for (auto const &item : planets)
    FLUSH_STDOUT_OF(planets, item.data(), item.capacity());

  std::unordered_map<SolarSystem, std::string> star_with_note;
  std::for_each(planets.cbegin(),
                planets.cend(),
                [&](const std::string &label)
                {
                  SolarSystem s{.star_name = label};
                  if (!star_with_note.contains(s))
                  {
                    star_with_note[s] = std::to_string(label.size());
                  }
                });
  for (auto const &item : star_with_note)
    FLUSH_STDOUT_OF(star_with_note, item.first, item.second);

  std::random_device rd;
  std::mt19937 num_generator(rd());
  // NOTE: std::normal_distribution<>::operator() requires a mutable std::mt19937 object
  //  (or any other random number generator) to generate random numbers.
  std::normal_distribution<> dist;
  [&dist, &star_with_note](std::mt19937 &ng)
  {
    double num = std::clamp<double>(dist(ng), -10, 10);
    for (const auto &[k, _] : star_with_note)
      std::cout << k << "+" << num << "\n";
  }(num_generator);

  return 0;
}