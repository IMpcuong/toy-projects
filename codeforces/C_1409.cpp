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
  ar<int, 3> params;
  generate(all(params), nxt<int>);
  auto &[n, x, y] = params;

  // + x < y
  // + n distinct positive integers
  // + a_1 < a_2 < ... < a_n && (a_{i + 3} - a_{i + 2} = a_{i + 1} - a_i)

  vector<int> ans(n);
  if (n == 2)
  {
    println(x, y);
    return;
  }

  int start = 1;
  int optim_epoch = 1;
  while (start <= x)
  {
    int delta = y - start;
    int epoch_cnt = n - 1;
    if (delta % epoch_cnt != 0)
    {
      start++;
      continue;
    }

    int epoch = delta / epoch_cnt;
    if ((x - start) % epoch == 0)
    {
      optim_epoch = max(optim_epoch, epoch);
      break;
    }
    start++;
  }

  auto find_max_divisor = [](const int &num) -> int
  {
    auto upper = static_cast<int>(ceil(sqrt(num)));
    int max_div = 1;
    for (int i = 1; i <= upper; i++)
    {
      if (num % i != 0)
        continue;

      max_div = max(max_div, i);
    }

    return max_div;
  };

  if (optim_epoch == 1 && x != 1)
  {
    int md = find_max_divisor(y - x);
    md = md > 1 ? md : y - x;
    optim_epoch = md;
    while (x > 0)
      x -= md;
    x = x > 0 ? x : x + md;
    start = x;
  }

  ans[0] = start;
  for (int i = 1; i < n; i++)
    ans[i] = ans[i - 1] + optim_epoch;

  cout << ans << "\n";
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
