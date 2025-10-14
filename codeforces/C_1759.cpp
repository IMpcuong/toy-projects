#include <algorithm>
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
  auto l = nxt<ll>(), r = nxt<ll>();
  auto min_delta = nxt<ll>();
  auto from = nxt<ll>(), to = nxt<ll>();

  if (from == to)
  {
    println(0);
    return;
  }
  if (from - l < min_delta && r - from < min_delta)
  {
    println(-1);
    return;
  }

  int steps = 1;
  ll cur_delta = to - from;
  if (abs(cur_delta) >= min_delta)
  {
    println(steps);
    return;
  }

  ll go_l = from - l;
  int l_steps = 1;
  bool have_l_path = false;
  if (go_l + cur_delta >= min_delta)
  {
    have_l_path = true;
    l_steps++;
    if (go_l < min_delta)
      l_steps++;
  }

  ll go_r = r - from;
  int r_steps = 1;
  bool have_r_path = false;
  if (go_r - cur_delta >= min_delta)
  {
    have_r_path = true;
    r_steps++;
    if (go_r < min_delta)
      r_steps++;
  }

  if (!have_l_path && !have_r_path)
    steps = -1;
  if (have_l_path && !have_r_path)
    steps = l_steps;
  if (have_r_path && !have_l_path)
    steps = r_steps;
  if (have_l_path && have_r_path)
    steps = min(l_steps, r_steps);
  println(steps);
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
