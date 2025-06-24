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
  auto n = nxt<int>();
  auto m = nxt<int>();
  vector<ll> flowers(n);
  ranges::generate(flowers, nxt<ll>);
  vector<ll> minimums(m);
  ranges::generate(minimums, nxt<ll>);

  auto reverse_minimums = minimums;
  ranges::reverse(reverse_minimums);

  vector<pair<ll, int>> minimums_with_idx(m);
  for (int i = 0; i < m; i++)
    minimums_with_idx[i] = make_pair(minimums[i], i);
  ranges::sort(minimums_with_idx,
      [](const auto &p1, const auto &p2) -> bool
      {
        if (p1.first == p2.first)
          return p1.second < p2.second;

        return p1.first < p2.first;
      });

  auto can_pass_the_rest_lower_bounds = [&](const int &ignore_idx) -> bool
  {
    auto reverse_minimums_cp = reverse_minimums;
    bool first_match = true;
    for (int i = 0; i < n; i++)
    {
      if (reverse_minimums_cp.empty())
        return true;

      if (ignore_idx != -1 &&
          first_match &&
          minimums[ignore_idx] == reverse_minimums_cp.back())
      {
        first_match = false;
        --i;
        reverse_minimums_cp.pop_back();
        continue;
      }

      if (flowers[i] < reverse_minimums_cp.back())
        continue;

      reverse_minimums_cp.pop_back();
    }

    return reverse_minimums_cp.empty();
  };

  if (can_pass_the_rest_lower_bounds(-1))
  {
    println(0);
    return;
  }

  int l = 0;
  int r = m - 1;
  ll ans = -1;
  vector<bool> picked(m, false);
  while (l <= r)
  {
    int m = (l + r) / 2;
    ll removable_by_wand = minimums_with_idx[m].first;

    int removable_idx = minimums_with_idx[m].second;
    for (int i = 0; i < m; i++)
    {
      if (minimums[i] == removable_by_wand && !picked[i])
      {
        removable_idx = min(removable_idx, i);
        picked[i] = true;
      }
    }

    if (can_pass_the_rest_lower_bounds(removable_idx))
    {
      ans = removable_by_wand;
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }

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
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
