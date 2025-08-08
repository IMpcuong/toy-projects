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

void remove_adjacent_parent_node_from(const int &cur, const int &parent,
    vector<vector<int>> &adjacents, vector<ll> &total_leaf_of)
{
  int adj_quan = sza(adjacents[cur]);
  for (int i = 0; i < adj_quan; i++)
  {
    int node = adjacents[cur][i];
    if (node == parent)
    {
      adjacents[cur][i] = adjacents[cur].back();
      adjacents[cur].pop_back();
      adj_quan--;

      if (adjacents[cur].empty())
      {
        total_leaf_of[parent]++;
        return;
      }

      i--; // @Hack: After swapping, adjacents[cur].back() := {index: i, traversed: false}.
    }
    else
    {
      remove_adjacent_parent_node_from(node /*cur=*/, cur /*parent=*/,
          adjacents, total_leaf_of);
      total_leaf_of[cur] += total_leaf_of[node];
      // println(cur, "->", node);
    }
    // total_leaf_of[node]++; // @Hack: Counting itself as one of the parent's children.
  }
}

void solve()
{
  auto vertices = nxt<int>();
  vector<vector<int>> adjacents(vertices);
  int edge_quan = vertices - 1;
  while (edge_quan)
  {
    auto vert1 = nxt<int>();
    auto vert2 = nxt<int>();
    adjacents[vert1 - 1].emplace_back(vert2 - 1);
    adjacents[vert2 - 1].emplace_back(vert1 - 1);
    edge_quan--;
  }

  auto guesses = nxt<int>();
  vector<pair<int, int>> pos_predictions(guesses);
  for (int i = 0; i < guesses; i++)
  {
    pos_predictions[i].first  = nxt<int>();
    pos_predictions[i].second = nxt<int>();
  }

  vector<ll> total_leaf_of(vertices, 0LL);
  int root_node = 0;
  int parent_node = -1;
  remove_adjacent_parent_node_from(root_node, parent_node, adjacents, total_leaf_of);

  for (const auto &pred : pos_predictions)
  {
    ll f_leaf_quan = total_leaf_of[pred.first - 1];
    f_leaf_quan = f_leaf_quan == 0 ? 1 : f_leaf_quan;
    ll s_leaf_quan = total_leaf_of[pred.second - 1];
    s_leaf_quan = s_leaf_quan == 0 ? 1 : s_leaf_quan;
    ll ans = f_leaf_quan * s_leaf_quan;
    println(ans);
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
