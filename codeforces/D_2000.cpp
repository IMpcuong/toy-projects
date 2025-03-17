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

constexpr char _L = 'L';
constexpr char _R = 'R';

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

ll solve()
{
  auto len = nxt<int>();
  vector<long> a(len);
  generate(all(a), nxt<long>);
  auto s = nxt<string>();

  vector<ll> inc_sum(len + 1);
  ll s_tmp = 0;
  for (int i = 0; i < len; i++)
  {
    s_tmp += a[i];
    inc_sum[i] = s_tmp;
  }
  inc_sum.insert(inc_sum.begin(), 0);

  // cout << inc_sum << "\n";

  ll sum = 0;
  int l = 0;
  int r = len - 1;
  while (r > l)
  {
    while (l < len && s[l] == _R)
      l++;
    while (r >= 0 && s[r] == _L)
      r--;
    if (l < r)
    {
      // @Note:
      //  + l < r
      //  + sum(a[i] | l <= i <= r)
      //      = a[l] + a[l + 1] + ... + a[r - 1] + a[r]
      //      = sum(a[i] | 1 <= i <= r) - sum(a[i] | 1 <= i <= l - 1)
      sum += inc_sum[r + 1] - inc_sum[l];
      l += 1;
      r -= 1;
    }
  }

  return sum;
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
