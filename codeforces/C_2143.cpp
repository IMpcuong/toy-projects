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

struct adjacent
{
  int     idx;
  int32_t gt_val;
  int32_t lt_val;
};

struct node
{
  vector<int> order;
};

bool is_node_equal_leaf(vector<vector<adjacent>> adjacents, int parent, int self)
{
  return sza(adjacents[self]) == 1 && adjacents[self].front().idx == parent;
}

void dfs(vector<vector<adjacent>> &adjacents, vector<node> &nodes,
    int parent, int cur)
{
  if (is_node_equal_leaf(adjacents, parent, cur))
  {
    nodes[cur].order.emplace_back(cur);
    return;
  }

  for (const auto &child : adjacents[cur])
  {
    if (child.idx == parent)
      continue;

    dfs(adjacents, nodes, cur /*parent=*/, child.idx /*cur=*/);
  }

  deque<int> cur_order = {cur};
  for (const auto &child : adjacents[cur])
  {
    if (child.idx == parent)
      continue;

    if (child.gt_val > child.lt_val)
    {
      ranges::reverse(nodes[child.idx].order);
      for (const auto &idx : nodes[child.idx].order)
        cur_order.emplace_front(idx);
    }
    else
    {
      for (const auto &idx : nodes[child.idx].order)
        cur_order.emplace_back(idx);
    }
  }
  nodes[cur].order = vector(all(cur_order));
}

void solve()
{
  auto verts = nxt<int>();
  vector<vector<adjacent>> adjacents(verts);
  int verts_cp = verts - 1;
  while (verts_cp)
  {
    auto from = nxt<int>() - 1;
    auto to   = nxt<int>() - 1;
    auto gt   = nxt<int32_t>();
    auto lt   = nxt<int32_t>();
    adjacents[from].emplace_back(adjacent{to, gt, lt});
    adjacents[to].emplace_back(adjacent{from, lt, gt});

    verts_cp--;
  }

  vector<node> nodes(verts);
  int root = 0;
  dfs(adjacents, nodes, -1 /*parent=*/, root /*cur=*/);
  vector<int> ans(verts);
  for (int i = 0; i < sza(nodes[root].order); i++)
  {
    int idx = nodes[root].order[i];
    ans[idx] = i + 1;
  }

  cout << ans << "\n";
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
