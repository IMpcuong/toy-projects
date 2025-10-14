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
  string sep;
  for (const T &x : v)
    os << sep << x, sep = " ";
  return os;
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
  vector<ll> points(n);
  ranges::generate(points, nxt<ll>);
  auto points_cp = points;
  ranges::sort(points_cp);

  //
  // @Note:
  //  + f_point([l_1; r_1]) + ... + f_point([l_n; r_n]) = len([l_1; r_1]) + ... + len([l_n; r_n])
  //  + len([a; b]) = b - a + 1
  //  + 1 <= i, j <= n
  //  + p_i := a fixed point
  //  + f_point(p_i) = sum({p_i - p_j + 1 | j < i}) + sum({p_j - p_i + 1 | j >= i})
  //      = (1 * n) + (p_i * i) - [p_i * (n - i)] + sum({p_j | j >= i}) - sum({p_j | j < i})
  //      = n + p_i * (2 * i - n) + sufffix_sum - prefix_sum
  //
  ll prefix_sum = 0;
  ll suffix_sum = accumulate(all(points_cp), 0LL);
  map<ll, ll> f_point;
  for (int i = 0; i < n; i++)
  {
    ll cur_p = points_cp[i];
    prefix_sum += cur_p;
    suffix_sum -= cur_p;
    f_point[cur_p] = n + cur_p * (2 * (i + 1) - n) + suffix_sum - prefix_sum;
  }

  for (auto &p : points)
    p = f_point[p];
  cout << points << "\n";
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
