#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -g -Wall -Wextra -O3 tmpl.cpp -o out

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

ll solve()
{
  auto n = nxt<long>();
  auto k = nxt<long>();
  vector<ll> a(n);
  generate(all(a), nxt<ll>);

  ll ans = 0LL;
  ll orig_sum = accumulate(all(a), ans) % MOD;

  ll max_segment_sum = -INF;
  ll cur_sum = 0LL;
  for (const auto &v : a)
  {
    cur_sum = max(cur_sum + v, v);
    max_segment_sum = max(max_segment_sum, cur_sum);
  }
  max_segment_sum = max(ans, max_segment_sum) % MOD; // @Note: x % MOD
  // println(max_segment_sum);

  ll extended_sum = 1LL;
  for (int i = 0; i < k; i++)
  {
    extended_sum *= 2;
    extended_sum %= MOD;
  }
  extended_sum -= 1; // @Note: (2^k - 1) % MOD
  extended_sum *= max_segment_sum; // @Note: (x % MOD) * ((2^k - 1) % MOD)
  // @Note:
  //  + (x . y) % MOD == ((x % MOD) . (y % MOD)) % MOD
  //  + . := {+, -, *, /}
  extended_sum %= MOD;

  // @Note:
  //  + sum := (orig_sum + extended_sum) < 0.
  //  + sum % MOD < 0 && |sum % MOD| >= 1.
  //  -> remain > 0 <-> sum += MOD.
  ans = (orig_sum + extended_sum + MOD) % MOD;
  return ans;
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
    println(solve());
  }
}
