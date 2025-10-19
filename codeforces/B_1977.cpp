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

const char *_Y = "YES";
const char *_N = "NO";

void solve()
{
  auto bin_dec = nxt<long>();

  const int _max_sz = 31;
  vector<int> bits(_max_sz, 0);
  auto max_pos = static_cast<int>(ceil(log2(bin_dec)));
  auto min_pos = static_cast<int>(floor(log2(bin_dec)));
  auto upper_pow = static_cast<long>(pow(2, max_pos));
  auto lower_pow = static_cast<long>(pow(2, min_pos));
  int furthest_pos = min_pos;
  if (upper_pow - bin_dec < bin_dec - lower_pow)
    furthest_pos = max_pos;
  bits[furthest_pos] = 1;

  bin_dec = static_cast<long>(pow(2, furthest_pos)) - bin_dec;
  if (bin_dec & 1)
  {
    bits[0] = -1;
    bin_dec--;
  }
  int i = 1;
  while (bin_dec != 0 && i < furthest_pos)
  {
    auto adjust = static_cast<long>(pow(2, i));
    if (bits[i - 1] != 0)
      continue;
    if (bin_dec < 0)
    {
      bits[i] = 1;
      bin_dec += adjust;
    }
    else
    {
      bits[i] = -1;
      bin_dec -= adjust;
    }
    i++;
  }
  bits.shrink_to_fit();

  println(sza(bits));
  cout << bits << "\n";
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
