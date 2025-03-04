#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -g -Wall -Wextra -O2 tmpl.cpp -o out

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

bool detect_beautiful_seq(const vector<int> &prey)
{
  int prey_cnt = sza(prey);
  if (prey_cnt == 1)
  {
    if (prey[0] == 1)
      return true;
    else
      return false;
  }

  for (int i = 0; i < prey_cnt; i++)
  {
    i += prey[i];
    if (i == prey_cnt - 1)
      return true;
  }

  return false;
}

int solve()
{
  int len;
  cin >> len;

  vector<int> seq(len);
  for (int i = 0; i < len; i++)
    cin >> seq[i];

  if (detect_beautiful_seq(seq))
    return 0;

  //
  // @Note:
  //  + dp[i] := minimum removals at state i_th.
  //  + i_th state := seq[i..len - 1] if it was already beautified.
  //
  vector<int> dp(len, INF);
  dp[len - 1] = 1; // @Note: The rightmost one only can be deleted.

  auto get_dp = [=](int last) -> int
  {
    if (last == len)
      return 0;
    if (last > len)
      return INF;
    return dp[last];
  };
  for (int i = len - 2; i >= 0; i--)
  {
    dp[i] = min(dp[i + 1] + 1 /* remove seq[i] */,
                get_dp(i + seq[i] + 1) /* make seq[i + seq[i] + 1..len - 1] beautiful */);
    println(i, dp[i]);
  }

  return dp[0];
}

int main()
{
  ios_base::sync_with_stdio(0);
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
