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
  auto one_sq_quan = nxt<int>();
  auto two_sq_quan = nxt<int>();

  const int max_one_sq_per_screen = 7;
  const int max_two_sq_per_screen = 2;
  const int screen_area = 5 * 3;

  if (one_sq_quan == 0 && two_sq_quan == 0)
  {
    println(0);
    return;
  }

  if (one_sq_quan <= max_one_sq_per_screen &&
      two_sq_quan <= max_two_sq_per_screen)
  {
    println(1);
    return;
  }

  if (two_sq_quan == 0)
  {
    int one_sq_screen_quan = one_sq_quan / screen_area;
    if (one_sq_quan > max_one_sq_per_screen && one_sq_quan % screen_area)
      one_sq_screen_quan++;

    println(one_sq_screen_quan);
  }
  else if (one_sq_quan == 0)
  {
    int two_sq_screen_quan = ceildiv(two_sq_quan, max_two_sq_per_screen);
    println(two_sq_screen_quan);
  }
  else
  {
    int screen_quan = ceildiv(two_sq_quan, max_two_sq_per_screen);
    int left_pos_for_one_sq = screen_quan * screen_area - two_sq_quan * 4;
    if (left_pos_for_one_sq > one_sq_quan)
      println(screen_quan);
    else
      println(screen_quan + ceildiv(one_sq_quan - left_pos_for_one_sq, screen_area));
  }
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
