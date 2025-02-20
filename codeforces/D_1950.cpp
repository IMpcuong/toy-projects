#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -Wall -Wextra -O2 tmpl.cpp -o out -v

using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

template <typename T_container,
          typename T = typename enable_if<!is_same<T_container, string>::value,
                                          typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
  os << '{';
  string sep;
  for (const T &x : v)
    os << sep << x, sep = ", ";
  return os << '}';
}

template <typename... Args>
void print(const Args &...args)
{
  bool end = true;
  ((std::cout << (end ? (end = false, "") : " ") << args), ...);
}

template <typename... Args>
void println(const Args &...args)
{
  bool end = true;
  ((std::cout << (end ? (end = false, "") : " ") << args), ...) << "\n";
}

void dbg_out() { cerr << endl; }

template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
  cerr << ' ' << H;
  dbg_out(T...);
}

// #define LOCAL 1

#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define us unsigned shor
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

const string Y = "YES";
const string N = "NO";

bool determine_binary_form_of_dec_num(int dec_num)
{
  if (dec_num == 1)
    return true;
  while (dec_num > 0)
  {
    if (dec_num % 10 > 1)
      return false;
    dec_num /= 10;
  }
  return true;
}

auto binary_decimal_list = []() -> vector<int>
{
  vector<int> out;
  out.reserve(MAX_N);
  for (int num = 2; num < MAX_N; num++)
  {
    if (!determine_binary_form_of_dec_num(num))
      continue;
    out.emplace_back(num);
  }
  return out;
}();

bool is_product_by_only_binary_dec(int target)
{
  if (target == 1)
    return true;

  bool satisfied = false;
  for (const auto &bin_decimal : binary_decimal_list)
  {
    if (target % bin_decimal == 0)
    {
      target /= bin_decimal;
      satisfied |= is_product_by_only_binary_dec(target);
    }
  }
  return satisfied;
}

string solve()
{
  int n;
  cin >> n;

  if (determine_binary_form_of_dec_num(n))
    return Y;

  bool valid = is_product_by_only_binary_dec(n);
  return valid ? Y : N;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++)
  {
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    println(solve());
  }
}
