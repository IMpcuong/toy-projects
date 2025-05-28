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

void solve()
{
  auto n = nxt<int>();
  vector<int> parent(n);
  generate(all(parent), nxt<int>);
  vector<int> permu(n);
  generate(all(permu), nxt<int>);

  map<int, int> node_prio;
  for (int i = 0; i < n; i++)
    node_prio[permu[i]] = i;

  auto contains_ancestor_behind = [&](const int &node_val) -> bool
  {
    int parent_val = parent[node_val - 1];
    return node_prio[parent_val] > node_prio[node_val];
  };

  vector<int> dist_by_order(n); // @Note: dist(root, cur_node) && order := permu.
  for (int j = 0; j < n; j++)
  {
    int cur_node = permu[j];
    if (contains_ancestor_behind(cur_node))
    {
      println(-1);
      return;
    }

    dist_by_order[cur_node - 1] = j;
  }

  vector<int> edge(n);
  int root = permu[0]; // Or: parent[i] = i + 1.
  for (int k = 0; k < n; k++)
  {
    if (parent[k] == root)
    {
      if (root == k + 1)
        edge[k] = 0;
      else
        edge[k] = dist_by_order[k];

      continue;
    }

    int weight = dist_by_order[k] - dist_by_order[parent[k] - 1];
    edge[k] = weight;
  }

  cout << edge << "\n";
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
