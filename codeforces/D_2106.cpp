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

  auto can_pass_the_rest_lower_bounds = [&](const int &ignore_idx = -1) -> bool
  {
    bool first_match = true;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
      if (j == m)
        return true;

      if (ignore_idx != -1 && ignore_idx == j && first_match)
      {
        first_match = false;
        --i;
        if (j < m)
          j++;
        continue;
      }

      if (flowers[i] < minimums[j])
        continue;

      if (j < m)
        j++;
    }

    return j == m;
  };

  if (can_pass_the_rest_lower_bounds())
  {
    println(0);
    return;
  }

  vector<int> prefix(m);
  int j = 0;
  for (int i = 0; i < m; i++)
  {
    while (j < n && flowers[j] < minimums[i])
      j++;
    prefix[i] = j;
    j++;
  }

  vector<int> suffix(m);
  j = n - 1;
  for (int i = m - 1; i >= 0; i--)
  {
    while (j >= 0 && flowers[j] < minimums[i])
      j--;
    suffix[i] = j;
    j--;
  }

  // cout << prefix << "\n";
  // cout << suffix << "\n";

  ll max_v = *ranges::max_element(minimums) + 1;
  ll ans = max_v;
  for (int i = 0; i < m; i++)
  {
    int last_idx_prefix  = i == 0     ? -1 : prefix[i - 1];
    int first_idx_suffix = i == m - 1 ?  n : suffix[i + 1];
    if (last_idx_prefix < first_idx_suffix)
      ans = min(ans, minimums[i]);
  }

  println(ans == max_v ? -1 : ans);
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
