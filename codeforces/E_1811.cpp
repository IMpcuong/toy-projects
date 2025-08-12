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

const int _ignored = 4;

void solve()
{
  auto query_idx = nxt<ll>();

  const int _upper_expo = 12;
  array<ll, _upper_expo + 1> ignorable_quan_by_expo;
  ignorable_quan_by_expo[1] = 1;
  for (int i = 2; i <= _upper_expo; i++)
    ignorable_quan_by_expo[i] = 8 * ignorable_quan_by_expo[i - 1];

  auto convert_to_idx_from = [&](ll num) -> ll
  {
    ll idx = num;
    int expo = 1;
    while (num)
    {
      int digit = num % 10;
      if (digit < _ignored && expo > 1)
        idx -= digit * ignorable_quan_by_expo[expo - 1];
      if (digit >= _ignored || digit == 0)
      {
        if (expo == 1)
        {
          idx -= ignorable_quan_by_expo[expo];
        }
        else
        {
          ll removable_start_with_ignored_digit_quan = static_cast<ll>(pow(10, double(expo - 1)));
          idx -= (digit - 1) * ignorable_quan_by_expo[expo - 1] + removable_start_with_ignored_digit_quan;
        }
      }

      expo++;
      num /= 10;
    }

    return idx;
  };

  ll ans = -1;
  ll l = 1;
  ll r = 1e12;
  while (l <= r)
  {
    ll mid_num = l + (r - l) / 2;
    ll idx = convert_to_idx_from(mid_num);
    if (idx > query_idx)
      r = mid_num - 1;
    else if (idx < query_idx)
      l = mid_num + 1;
    if (idx == query_idx)
    {
      ans = idx;
      break;
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
    cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
