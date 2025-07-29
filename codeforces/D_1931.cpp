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
  auto x = nxt<ll>();
  auto y = nxt<ll>();

  vector<ll> a(n);
  ranges::generate(a, nxt<ll>);

  //
  // @Note:
  //  + i < j < n
  //  + (a[i] + a[j]) mod x = 0 <=> (a[i] mod x + a[j] mod x) mod x = 0
  //                            <=> a[i] mod x = (x - a[j] mod x) mod x
  //  + (a[i] - a[j]) mod y = 0 <=> a[i] mod y = a[j] mod y
  //

  ll pair_cnt = 0;
  map<pair<ll, ll>, int> valid;
  for (int j = 0; j < n; j++)
  {
    ll aj_mod_x = a[j] % x;
    ll aj_mod_y = a[j] % y;
    ll expected_ai_mod_x = (x - aj_mod_x) % x;

    auto k = make_pair(expected_ai_mod_x, aj_mod_y);
    if (valid.count(k))
      pair_cnt += valid[k];

    auto kj = make_pair(aj_mod_x, aj_mod_y);
    if (valid.count(kj))
    {
      valid[kj]++;
      continue;
    }
    valid[kj] = 1;
  }

  // for (const auto &[p, f] : valid)
  //   print(p.first, "+", p.second, ":=", f, " ");

  println(pair_cnt);
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
