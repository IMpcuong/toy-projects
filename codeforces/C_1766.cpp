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
concept Input_Streamable_Type = requires(T stdin_data)
{
  cin >> stdin_data;
};

template <Input_Streamable_Type IST>
inline IST nxt()
{
  IST x;
  cin >> x;
  return x;
}

const char *_Y = "YES";
const char *_N = "NO";
const char _B = 'B';
const char _W = 'W';

void solve()
{
  const int row = 2;
  auto col = nxt<int>();
  ar<string, row> mat;
  for (auto &line : mat)
  {
    line.reserve(col);
    line = nxt<string>();
  }

  ar<bool, row> dp;
  fill_n(dp.begin(), row, false);
  for (int j = 0; j < col; j++)
  {
    auto nxt_dp = dp;
    int cnt_valid_tail = 0;
    int valid_tail = -1;
    for (int i = 0; i < row; i++)
    {
      if (mat[i][j] == _W)
      {
        nxt_dp[i] = false;
        continue;
      }
      if (mat[i][j] == _B)
      {
        if (j == 0)
        {
          nxt_dp[i] = true;
          continue;
        }
        if (mat[i][j - 1] == _B && dp[i])
        {
          nxt_dp[i] = true;
          cnt_valid_tail++;
          valid_tail = i;
        }
      }
    }
    if (j != 0 && cnt_valid_tail == 1)
    {
      if (mat[1 - valid_tail][j] == _B)
      {
        nxt_dp[1 - valid_tail] = true;
        nxt_dp[valid_tail] = false;
      }
    }

    dp = nxt_dp;
  }

  for (const auto &can_end_by_row : dp)
  {
    if (can_end_by_row)
    {
      println(_Y);
      return;
    }
  }
  println(_N);
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
