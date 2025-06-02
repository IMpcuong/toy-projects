#include <algorithm>
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

template <typename T>
struct nxt_t
{
  T hold;

  inline T operator()()
  {
    cin >> hold;
    return hold;
  }
};

struct prev_node
{
  int idx;
  ll weight_to_cur;
};

void solve()
{
  auto n = nxt<int>();
  auto m = nxt<int>();

  vector<ll> checkpoints(n);
  generate(all(checkpoints), nxt_t<ll>());

  vector<ar<ll, 3>> entries(m);
  for (int i = 0; i < m; i++)
    generate(all(entries[i]), nxt_t<ll>());

  vector<vector<prev_node>> prev_neighbors_of(n);
  for (int i = 0; i < m; i++)
  {
    int from = entries[i][0] - 1;
    int to = entries[i][1] - 1;
    ll w = entries[i][2];
    prev_neighbors_of[to].emplace_back(prev_node{from, w});
  }

  auto can_robot_travel_with_fixed_batteries = [&](const ll &expected_batt) -> ll
  {
    //
    // @Note:
    //  + i     := index of the current node.
    //  + dp[i] := total and maximum-possible batteries which is held by this robot.
    //
    vector<ll> dp(n, -1);
    dp[0] = min(checkpoints[0], expected_batt);

    for (int i = 1; i < n; i++)
    {
      ll max_total_prev_batt = dp[i];
      for (const auto &prev_node : prev_neighbors_of[i])
      {
        // @Note: node[prev_node.idx] can be reachable from node[0].
        if (dp[prev_node.idx] == -1)
          continue;

        if (dp[prev_node.idx] < prev_node.weight_to_cur)
          continue;

        max_total_prev_batt = max(max_total_prev_batt, dp[prev_node.idx] + checkpoints[i]);
      }

      dp[i] = min(max_total_prev_batt, expected_batt);
    }

    if (dp[n - 1] == -1)
      return false;

    return true;
  };

  ll min_batt = 0LL;
  ll max_batt = INF + 5;

  // bool tmp = can_robot_travel_with_fixed_batteries(0);
  // println(tmp);

  ll ans = -1;
  while (min_batt <= max_batt)
  {
    ll med_batt = (min_batt + max_batt) / 2;
    // println(min_batt, max_batt, med_batt);
    if (can_robot_travel_with_fixed_batteries(med_batt))
    {
      max_batt = med_batt - 1;
      ans = med_batt;
    }
    else
    {
      min_batt = med_batt + 1;
    }
  }

  println(ans);
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
