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

const int _sz = 3;

void solve()
{
  auto n = nxt<int>();
  auto bin_str = nxt<string>();

  // @Note:
  //   state := dp[last_chr][delta + 1]:
  //     + last_chr := last character of our remaining/kept string
  //                := {0: '0', 1: '1', 2: ''}
  //     + delta    := kept_zero_quan - kept_one_quan := {-1, 0, 1}
  //   state := maximum length of an alternating subsequence
  vector<ar<int, _sz>> dp(_sz, {-INF, -INF, -INF});

  // Kept string with empty length.
  dp[2][0 + 1] = 0;
  for (const auto &chr : bin_str)
  {
    auto nxt_dp = dp;

    int cur_chr = chr - '0';
    for (const auto &last_chr : {0, 1, 2})
    {
      for (auto delta : {-1, 0, 1})
      {
        int kept_str_len = dp[last_chr][delta + 1];
        if (kept_str_len == -INF)
          continue;

        if (last_chr == 2 || last_chr != cur_chr)
        {
          delta += (cur_chr == 0 ? 1 : -1);
          if (abs(delta) <= 1)
            nxt_dp[cur_chr][delta + 1] = max(nxt_dp[cur_chr][delta + 1], kept_str_len + 1);
        }
      }
    }

    dp = nxt_dp;
    // println(dp);
  }

  int zero_quan = ranges::count(bin_str, '0');
  int one_quan = n - zero_quan;
  int total_delta = zero_quan - one_quan;

  int max_kept_str_len = -INF;
  for (const auto &last_chr : {0, 1, 2})
  {
    for (auto kept_delta : {-1, 0, 1})
    {
      int kept_str_len = dp[last_chr][kept_delta + 1];
      if (kept_str_len == -INF)
        continue;

      // println(total_delta, delta);
      int deleted_delta = total_delta - kept_delta;
      if (abs(deleted_delta) <= 1)
        max_kept_str_len = max(max_kept_str_len, kept_str_len);
    }
  }

  if (max_kept_str_len == -INF)
    println(-1);
  else
    println(n - max_kept_str_len);
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
