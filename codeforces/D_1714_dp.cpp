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
  auto target = nxt<string>();
  auto set_quan = nxt<int>();
  vector<string> sub_seqs(set_quan);
  ranges::generate(sub_seqs, nxt<string>);

  int target_len = sza(target);
  struct interval
  {
    int belong_to;
    int l;
    int r;

    bool operator<(const interval &other) const
    {
      return this->l < other.l;
    }
  };
  vector<interval> seq_intervals;
  for (int i = 0; i < set_quan; i++)
  {
    string sub = sub_seqs[i];
    int sub_len = sza(sub);
    for (int j = 0; j < target_len - sub_len + 1; j++)
    {
      string sub_from_target = target.substr(j, sub_len);
      if (sub == sub_from_target)
        seq_intervals.emplace_back(interval{i /*belong_to=*/, j /*l=*/, j + sub_len - 1 /*r=*/});
    }
  }
  ranges::sort(seq_intervals, [](const auto &f, const auto &s) { return f < s; });
  if (seq_intervals.empty() || seq_intervals.front().l > 0)
  {
    println(-1);
    return;
  }
  // ranges::for_each(seq_intervals, [](const auto &si) { println(si.l, si.r, si.belong_to); });

  int interval_quan = sza(seq_intervals);
  struct state
  {
    int pick_quan = -1;
    interval tracer;
  };
  vector<state> dp(target_len);
  for (const auto &closure : seq_intervals)
  {
    int cur_l = closure.l;
    int cur_r = closure.r;
    if (cur_l == 0)
    {
      for (int r = cur_l; r <= cur_r; r++)
      {
        dp[r].pick_quan = 1;
        dp[r].tracer = closure;
      }
      continue;
    }

    // `cur_l`th position is reachable
    if (dp[cur_l - 1].pick_quan > 0)
    {
      int pick_quan_if_chose_cur = dp[cur_l - 1].pick_quan + 1;
      for (int r = cur_l; r <= cur_r; r++)
      {
        if (dp[r].pick_quan == -1)
        {
          dp[r].pick_quan = pick_quan_if_chose_cur;
          dp[r].tracer = closure;
        }
        if (dp[r].pick_quan > pick_quan_if_chose_cur)
        {
          dp[r].pick_quan = pick_quan_if_chose_cur;
          dp[r].tracer = closure;
        }
      }
    }
  }

  if (dp[target_len - 1].pick_quan == -1)
  {
    println(-1);
    return;
  }

  int optim_pick_tactic = dp[target_len - 1].pick_quan;
  println(optim_pick_tactic);
  auto closure = dp[target_len - 1].tracer;
  while (closure.l != 0)
  {
    println(closure.belong_to + 1, closure.l + 1);
    closure = dp[closure.l - 1].tracer;
  }
  println(closure.belong_to + 1, closure.l + 1); // l = 0
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
