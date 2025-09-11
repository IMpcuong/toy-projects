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

struct node
{
  int idx;
  ll weight_a;
  ll weight_b;
};

void traverse_tree_from(const int &parent, vector<vector<node>> &adjacents,
    vector<int> &optim_edge_quans, ll &wa_sum, vector<ll> &wb_pref_sums)
{
  if (adjacents[parent].empty())
    return;

  int adj_quan = sza(adjacents[parent]);
  for (int i = 0; i < adj_quan; i++)
  {
    int node_idx = adjacents[parent][i].idx;
    ll node_wa   = adjacents[parent][i].weight_a;
    ll node_wb   = adjacents[parent][i].weight_b;

    wa_sum += node_wa;
    wb_pref_sums.emplace_back(wb_pref_sums.back() + node_wb);

    int l = 0;
    int r = sza(wb_pref_sums) - 1;
    while (l <= r)
    {
      int m = l + (r - l) / 2;
      if (wb_pref_sums[m] <= wa_sum)
      {
        optim_edge_quans[node_idx] = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }

    traverse_tree_from(node_idx, adjacents,
        optim_edge_quans, wa_sum, wb_pref_sums);
    wb_pref_sums.pop_back();
    wa_sum -= node_wa;
  }
}

void solve()
{
  auto vertices = nxt<int>();
  vector<vector<node>> adjacents(vertices);
  for (int child = 1; child < vertices; child++)
  {
    auto parent = nxt<int>() - 1;
    auto weight_a = nxt<ll>();
    auto weight_b = nxt<ll>();
    adjacents[parent].emplace_back(node{child, weight_a, weight_b});
  }

// #define LOCAL
#ifdef LOCAL
  auto debug_node_childs_of = [&](const auto &idx) -> void
  {
    println("node:", idx);
    for (const auto &child : adjacents[idx])
      println(">>> child:", child.idx, "|", child.weight_a, child.weight_b);
  };

  debug_node_childs_of(0 /*idx=*/);
  debug_node_childs_of(3 /*idx=*/);
  debug_node_childs_of(4 /*idx=*/);
#endif

  ll wa_sum = 0LL;
  vector<ll> wb_pref_sums = {0};
  vector<int> optim_edge_quans(vertices, -1);
  int root = 0;
  traverse_tree_from(root, adjacents, optim_edge_quans, wa_sum, wb_pref_sums);

  optim_edge_quans.erase(optim_edge_quans.begin());
  cout << optim_edge_quans << "\n";
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
