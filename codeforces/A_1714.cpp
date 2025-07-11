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

void solve()
{
  ar<int, 3> params;
  ranges::generate(params, nxt<int>);

  auto &[n, sleep_h, sleep_m] = params;
  vector<pair<int, int>> alarms(n);
  for (int i = 0; i < n; i++)
  {
    alarms[i].first = nxt<int>();
    alarms[i].second = nxt<int>();
  }

  int delta_h = MAX_N;
  int delta_m = MAX_N;
  for (const auto &alarm : alarms)
  {
    int cur_h = alarm.first;
    int cur_m = alarm.second;

    int cur_delta_h = cur_h - sleep_h;
    int cur_delta_m = abs(cur_m - sleep_m);

    if ((sleep_h > cur_h) ||
        (sleep_h == cur_h && sleep_m > cur_m))
      cur_delta_h = cur_h + (24 - sleep_h);

    if (cur_m < sleep_m)
    {
      cur_delta_h--;
      cur_delta_m = 60 - cur_delta_m;
    }

    if (cur_delta_h < delta_h)
    {
      delta_h = cur_delta_h;
      delta_m = cur_delta_m;
      continue;
    }

    if (cur_delta_h == delta_h && cur_delta_m < delta_m)
    {
      delta_m = cur_delta_m;
      continue;
    }
  }

  println(delta_h, delta_m);
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
