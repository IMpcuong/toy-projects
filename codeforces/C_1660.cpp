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
  auto s = nxt<string>();
  int n = sza(s);

  const int _alphabet = 26;
  vector<vector<int>> dp(n + 1, vector<int>(_alphabet + 1, INF));
  dp[0][_alphabet] = 0; // @Note: All chars are paired state.
  for (int i = 1; i < n + 1; i++)
  {
    int chr_idx = s[i - 1] - 'a';

    // @Note: Iterates through all the waiting-to-pair chars -> update their state.
    for (int last_chr_idx = 0; last_chr_idx < _alphabet + 1; last_chr_idx++)
    {
      if (dp[i - 1][last_chr_idx] == INF)
        continue;

      // Delete s[i - 1]:
      dp[i][last_chr_idx] = min(dp[i][last_chr_idx], dp[i - 1][last_chr_idx] + 1);

      // Select s[i - 1]:
      if (last_chr_idx == _alphabet)
      {
        dp[i][chr_idx] = min(dp[i][chr_idx], dp[i - 1][_alphabet]);
        continue;
      }
      if (last_chr_idx == chr_idx)
        dp[i][_alphabet] = min(dp[i][_alphabet], dp[i - 1][chr_idx]);
      if (last_chr_idx != chr_idx)
        dp[i][chr_idx] = min(dp[i][chr_idx], dp[i - 1][last_chr_idx] + 1);
    }
  }

  // cout << dp[n] << "\n";
  println(dp[n][_alphabet]);
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
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
