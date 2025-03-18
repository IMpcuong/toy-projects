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
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

constexpr char _L = '0';
constexpr char _R = '1';

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

int solve()
{
  auto len = nxt<int>();
  auto sides = nxt<string>();

  int zeros = static_cast<int>(ranges::count(sides, _L));
  int ones = len - zeros;

  float ans = -1;
  float mid = float(len) / 2;

  if (zeros == ones)
    ans = 0;
  if (zeros > ones)
    ans = len;
  if (zeros < ones)
    ans = 0;

  int l_zeros = 0;
  int r_ones = ones;
  for (int br = 1; br < len; br++)
  {
    char l_char = sides[br - 1];
    if (l_char == _L)
      l_zeros++;
    else
      r_ones--;

    int half_l = ceil(float(br) / 2);
    int half_r = ceil(float(len - br) / 2);

    // println(br);
    // println(l_zeros, r_ones, half_l, half_r);

    if (l_zeros >= half_l && r_ones >= half_r)
    {
      float dist_old = abs(mid - ans);
      float dist_new = abs(mid - float(br));
      ans = dist_old > dist_new ? br : ans;
    }
  }

  return int(ans);
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
    println(solve());
  }
}
