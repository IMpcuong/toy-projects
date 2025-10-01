#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -g -Wall -Wextra -fsanitize=address -O3 tmpl.cpp -o out

using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

template <typename ...Args>
ostream &operator<<(ostream &os, const tuple<Args...> &t)
{
  os << '{';
  string sep;
  apply([&](auto &&...args) { ((os << sep << args, sep = ", "), ...); }, t);
  return os << '}';
}

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
  ((cout << (end ? (end = false, "") : " ") << args), ...);
}

template <typename... Args>
void println(const Args &...args)
{
  bool end = true;
  ((cout << (end ? (end = false, "") : " ") << args), ...) << "\n";
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
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
#define prec(k) cout << fixed << setprecision(k);
#define ceildiv(n, k) (((n) + (k) - 1) / (k))

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using point = complex<double>;

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

void solve()
{
  auto n = nxt<int>(); // n >= 2
  auto digit_str = nxt<string>();

  const char _z = '0';
  int zeros = ranges::count(digit_str, _z);
  if (n == 2)
  {
    if (zeros && digit_str[0] == _z)
    {
      println(digit_str[n - 1]);
      return;
    }
    println(digit_str);
    return;
  }

  if (zeros)
  {
    if (n == 3)
    {
      char first = digit_str[0];
      char last  = digit_str[n - 1];
      if (first == _z || last == _z)
        println(0);
      else
        println(first);

      return;
    }
    if (n > 3)
    {
      println(0);
      return;
    }
  }

  vector<int> digits;
  digits.reserve(n + 1);
  digits.emplace_back(0);
  for (const auto &d : digit_str)
    digits.emplace_back(d - '0');

  //
  // @Note:
  //  + state(dp[i].first)  := mergeless && min
  //  + state(dp[i].second) := merged && min
  //  + 0 <= i <= n - 1
  //
  vector<pair<int, int>> dp(n + 1, {0 , 0});
  for (int i = 1; i < n + 1; i++)
  {
    dp[i].first = dp[i - 1].first + digits[i];

    dp[i].second = (dp[i - 1].first - digits[i - 1])
      + (10 * digits[i - 1] + digits[i]);
    if (i > 2)
      dp[i].second = min(dp[i].second, dp[i - 1].second + digits[i]);
  }

  cout << dp << "\n";
  int ans = dp[n].second;
  println(ans);
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.exceptions(ios::badbit | ios::failbit);
  cin.tie(0);
  cout.tie(0);

  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++)
  {
    cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
