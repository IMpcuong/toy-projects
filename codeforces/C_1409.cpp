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

  int delta = y - x;

  auto find_divisors = [](const int &num) -> set<int>
  {
    auto upper = static_cast<int>(ceil(sqrt(num)));
    set<int> divs;
    for (int i = 1; i <= upper; i++)
    {
      if (num % i != 0)
        continue;

      divs.emplace(i);
      divs.emplace(num / i);
    }

    return divs;
  };

  int epoch_cnt = n - 1;
  int epoch = 1;
  int start = x;

  set<int> divs = find_divisors(delta);
  for (const auto &div : divs)
  {
    for (int i = 1; i <= epoch_cnt; i++)
    {
      int start_tmp = y - div * i;
      if (start_tmp > 0)
        start = min(start, start_tmp);
    }

    if (start + epoch_cnt * div >= y)
    {
      epoch = max(epoch, div);
      break;
    }
  }

  ans[0] = start;
  for (int i = 1; i < n; i++)
    ans[i] = ans[i - 1] + epoch;

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
