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

int cal_max_expo_of_two_divisible_by(auto num)
{
  int expo = 0;
  if (num & 1)
    return expo;

  while (num % 2 == 0)
  {
    num /= 2;
    expo++;
  }

  return expo;
}

void solve()
{
  auto n = nxt<int>();
  vector<ll> a(n);
  generate(all(a), nxt<ll>);

  ranges::sort(a, [](ll f, ll s) { return f >= s; });


  int n_tmp = n;
  int ops = 0;
  for (int i = 0; i < n; i++)
  {
    if (a[i] & 1)
      continue;

    ll dec_val = cal_max_expo_of_two_divisible_by(a[i]);
    n_tmp -= dec_val;
  }

  if (n_tmp <= 0)
  {
    println(ops);
    return;
  }

  int inc = 1;
  vector<int> expo_list(n);
  generate(all(expo_list), [&]() { return cal_max_expo_of_two_divisible_by(inc++); });
  ranges::sort(expo_list, [](int f, int s) { return f >= s; });

  // cout << expo_list << "\n";

  for (auto expo : expo_list)
  {
    if (expo == 0)
      continue;

    n_tmp -= expo;
    ops++;
    if (n_tmp <= 0)
    {
      println(ops);
      return;
    }
  }

  if (n_tmp > 0)
    println(-1);
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
