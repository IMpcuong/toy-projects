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

const char *_Y = "YES";
const char *_N = "NO";

void solve()
{
  ar<int, 4> params;
  ranges::generate(params, nxt<int>);

  auto &[v_quan, d12, d23, d13] = params;
  int double_shared_edge_quan = (d12 + d13) - d23;
  if (double_shared_edge_quan < 0 || double_shared_edge_quan & 1)
  {
    println(_N);
    return;
  }
  int shared_edge_quan = double_shared_edge_quan >> 1;
  int total_edge_quan = d23 + shared_edge_quan;
  if (total_edge_quan + 1 > v_quan ||
      shared_edge_quan > d12 || shared_edge_quan > d13)
  {
    println(_N);
    return;
  };

  println(_Y);
  stack<int> stock;
  while (v_quan > 3)
  {
    stock.push(v_quan);
    v_quan--;
  }

  int parent = 1;
  if (shared_edge_quan == 0)
  {
    int cache_intersect = parent;
    while (d12 - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      d12--;
      stock.pop();
    }
    println(parent, 2);

    parent = cache_intersect;
    while (d13 - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      d13--;
      stock.pop();
    }
    println(parent, 3);
  }
  else if (shared_edge_quan == min(d12, d13))
  {
    int cache_intersect = d12 == min(d12, d13) ? 2 : 3;
    int f_route = d12;
    int s_route = d13 - f_route;
    if (cache_intersect == 3)
    {
      f_route = d13;
      s_route = d12 - f_route;
    }

    while (f_route - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      f_route--;
      stock.pop();
    }
    println(parent, cache_intersect);

    parent = cache_intersect;
    while (s_route - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      s_route--;
      stock.pop();
    }
    println(parent, 5 - cache_intersect);
  }
  else
  {
    int shared_cache = shared_edge_quan;
    while (shared_edge_quan && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      shared_edge_quan--;
      stock.pop();
    }

    int cache_intersect = parent;
    int f_route = d12 - shared_cache;
    int s_route = d13 - shared_cache;

    while (f_route - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      f_route--;
      stock.pop();
    }
    println(parent, 2);

    parent = cache_intersect;
    while (s_route - 1 && !stock.empty())
    {
      println(parent, stock.top());
      parent = stock.top();
      s_route--;
      stock.pop();
    }
    println(parent, 3);
  }
  while (!stock.empty())
  {
    println(parent, stock.top());
    parent = stock.top();
    stock.pop();
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
