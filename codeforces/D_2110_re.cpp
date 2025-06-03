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

struct prev_node
{
  int idx;
  ll  weight_to_cur;
};

void solve()
{
  auto n = nxt<int>();
  auto m = nxt<int>();

  vector<ll> checkpoints(n);
  generate(all(checkpoints), nxt<ll>);

  vector<ar<ll, 3>> passages(m);
  for (int i = 0; i < m; i++)
    generate(all(passages[i]), nxt<ll>);

  vector<vector<prev_node>> past_neighbors_of(n);
  for (const auto &edge : passages)
  {
    int from  = edge[0] - 1; // @Note: array-idx started from 0.
    int to    = edge[1] - 1;
    ll weight = edge[2];

    past_neighbors_of[to].emplace_back(prev_node{from, weight});
  }

  auto has_route_through_with_guessed_batt_quan = [&](const ll &guessed_quan) -> bool
  {
    vector<int> dp(n, -1);
    // @Note: Keepin' the batteries on our pocket as small as possible.
    dp[0] = min(checkpoints[0], guessed_quan);

    for (int cur_node = 1; cur_node < n; cur_node++)
    {
      ll max_total_batt_before_pass_cur_node = dp[cur_node]; // @Note: Before passing the checkpoints[cur_node].

      for (const auto &prev_node : past_neighbors_of[cur_node])
      {
        // @Note: Cannot traverse from root (node[0]) through any route to reach node[prev_node.idx].
        if (dp[prev_node.idx] == -1)
          continue;

        // @Note: Cannot traverse from node[prev_node.idx] to node[cur_node] due to the
        //  lack of batteries quantity which is possessed by the robot (batteries were collected
        //  from checkpoints[0] -distinct-route-> checkpoints[prev_node.idx]).
        if (dp[prev_node.idx] < prev_node.weight_to_cur)
          continue;

        ll max_total_batt_after_pass_cur_node = dp[prev_node.idx] + checkpoints[cur_node];
        max_total_batt_before_pass_cur_node = max(max_total_batt_before_pass_cur_node,
            max_total_batt_after_pass_cur_node);
      }

      dp[cur_node] = min(max_total_batt_before_pass_cur_node, guessed_quan);
    }

    if (dp[n - 1] == -1)
      return false;

    return true;
  };

  ll ans = -1;
  ll min_held_batt = 0LL;
  ll max_held_batt = INF;
  while (min_held_batt <= max_held_batt)
  {
    ll mid_held_batt = (min_held_batt + max_held_batt) / 2;
    if (has_route_through_with_guessed_batt_quan(mid_held_batt))
    {
      max_held_batt = mid_held_batt - 1;
      ans = mid_held_batt;
    }
    else
    {
      min_held_batt = mid_held_batt + 1;
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
