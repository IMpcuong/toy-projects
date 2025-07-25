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
  auto digit_str = nxt<string>();
  auto sub_width = nxt<int>(); // sub_width < n

  auto q_quan = nxt<int>();
  struct query
  {
    int from;
    int to;
    int target;
  };
  vector<query> queries(q_quan);
  for (int i = 0; i < q_quan; i++)
  {
    queries[i].from   = nxt<int>();
    queries[i].to     = nxt<int>();
    queries[i].target = nxt<int>();
  }

  int n = sza(digit_str);
  const int _mod = 9;

  vector<long> pref_sums = {0};
  pref_sums.reserve(n + 1);
  for (const auto &digit_chr : digit_str)
    pref_sums.emplace_back(pref_sums.back() + (digit_chr - '0'));

  vector<vector<int>> mod_locs(_mod);
  for (int i = 0; i <= n - sub_width; i++)
  {
    int mod_v = (pref_sums[i + sub_width] - pref_sums[i]) % _mod;
    mod_locs[mod_v].emplace_back(i);
  }

  // cout << mod_locs << "\n";

  for (const auto &q : queries)
  {
    int left_border1 = -1;
    int left_border2 = -1;
    int after_all_left_border2 = left_border2;

    int static_mod = (pref_sums[q.to] - pref_sums[q.from - 1]) % _mod;
    for (int f_try = 0; f_try < _mod; f_try++)
    {
      for (int s_try = 0; s_try < _mod; s_try++)
      {
        if (((f_try * static_mod) % _mod + s_try) % _mod == q.target)
        {
          if (mod_locs[f_try].empty() || mod_locs[s_try].empty())
            continue;

          int diff_loc = 0;
          if (f_try == s_try)
          {
            if (sza(mod_locs[f_try]) < 2)
              continue;

            diff_loc = 1;
          }

          int maybe_left1 = mod_locs[f_try][0] + 1;
          int maybe_left2 = mod_locs[s_try][diff_loc] + 1;

          left_border1 = left_border1 == -1
            ? maybe_left1
            : min(left_border1, maybe_left1);

          int tmp_left_border2 = left_border2 == -1
            ? maybe_left2
            : min(left_border2, maybe_left2);
          if (tmp_left_border2 > left_border1)
            left_border2 = tmp_left_border2;

          after_all_left_border2 = after_all_left_border2 == -1
            ? maybe_left2
            : min(after_all_left_border2, tmp_left_border2);
        }
      }
    }

    if (left_border2 == -1)
      left_border2 = after_all_left_border2;
    println(left_border1, left_border2);
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
