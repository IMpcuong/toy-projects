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
  auto n = nxt<int>();
  vector<int> d(n);
  generate(all(d), nxt<int>);

  vector<ar<int, 2>> bound(n); // l := bound[i][0] && r := bound[i][1]
  for (int i = 0; i < n; i++)
    generate(all(bound[i]), nxt<int>);

  //
  // @Note:
  //  + i        := checkpoint i_th.
  //  + dp[i][0] := min_height possibly reached after each checkpoint.
  //  + dp[i][1] := max_height possibly reached after each checkpoint.
  //
  vector<ar<int, 2>> dp(n + 1);

  for (int j = 1; j < n + 1; j++)
  {
    int delta = d[j - 1] != 0 ? 1 : 0;
    int l = bound[j - 1][0];
    int r = bound[j - 1][1];
    if (l > dp[j - 1][1] + delta || r < dp[j - 1][0] + delta)
    {
      println(-1);
      return;
    }

    if (l > dp[j - 1][0])
      dp[j][0] = l;
    else
      dp[j][0] = dp[j - 1][0];

    if (r < dp[j - 1][1] + delta)
      dp[j][1] = r;
    else
      dp[j][1] = dp[j - 1][1] + delta;

    if (dp[j][0] > dp[j][1])
    {
      println(-1);
      return;
    }

    cout << dp[j] << "\n";
  }

  for (int k = n; k >= 1; k--)
  {
    if (d[k - 1] != -1)
      continue;

    int delta_r = abs(dp[k][1] - dp[k - 1][1]);
    if (delta_r == 1)
      d[k - 1] = 1;
    else
      d[k - 1] = 0;
  }

  // cout << dp << "\n";
  cout << d << "\n";
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
