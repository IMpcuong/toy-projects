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
  auto n = nxt<int>();
  vector<int> a(n);
  generate(all(a), nxt<int>);

  int max_v = *ranges::max_element(a);
  vector<vector<int>> dp(n + 1);
  dp[0] = vector(max_v + 1, MAX_N);
  for (int i = 1; i <= n; i++)
  {
    int nxt_num = a[i - 1];
    dp[i] = dp[i - 1];
    dp[i][nxt_num] = 1;
    for (int last_gcd = 1; last_gcd <= max_v; last_gcd++)
    {
      int cur_gcd = gcd(nxt_num, last_gcd);
      if (dp[i - 1][last_gcd] == MAX_N)
        continue;

      int take_nxt_num = min(dp[i][cur_gcd], dp[i - 1][last_gcd] + 1);
      int drop_nxt_num = dp[i - 1][cur_gcd];
      dp[i][cur_gcd] = min(drop_nxt_num, take_nxt_num);
    }
  }

  // cout << dp[n] << "\n";

  int ans_op = MAX_N;
  int ans_gcd = MAX_N;
  for (int each_gcd = 1; each_gcd <= max_v; each_gcd++)
  {
    bool divisible_by_all_num = true;
    for (const auto &num : a)
    {
      if (num % each_gcd != 0)
      {
        divisible_by_all_num = false;
        break;
      }
    }

    if (!divisible_by_all_num)
      continue;

    int min_merge_ops = dp[n][each_gcd];
    ans_gcd = min_merge_ops < ans_op ? each_gcd : ans_gcd;
    ans_op  = min(ans_op, min_merge_ops);
  }

  int ans_gcd_cnt = ranges::count_if(a, [&](const int &num) { return num == ans_gcd; });
  if (ans_gcd_cnt)
    println(n - ans_gcd_cnt);
  else
    println((ans_op - 1) + (n - 1));
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
