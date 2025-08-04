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

enum dir { down = 'D', right = 'R' };

void solve()
{
  auto rows = nxt<int>();
  auto cols = nxt<int>();

  //
  // @Note:
  //  + tampered_path.size()     = rows + cols - 1
  //  + tampered_path.begin_cell = {0, 0}
  //  + tampered_path.end_cell   = {rows - 1, cols - 1}
  //
  auto tampered_path = nxt<string>();

  vector<vector<ll>> terrains(rows);
  for (int r = 0; r < rows; r++)
  {
    vector<ll> cur_row(cols);
    ranges::generate(cur_row, nxt<ll>);

    terrains[r].reserve(cols);
    terrains[r] = cur_row;
  }

  int tampered_path_len = sza(tampered_path);
  assert(tampered_path_len == rows + cols - 2);

  const ll only_dim_sum_choice = 0L;
  int x = 0;
  int y = 0;
  for (const auto &hint : tampered_path)
  {
    if (hint == dir::down)
    {
      ll row_sum = 0;
      for (int j = 0; j < cols; j++)
        row_sum += terrains[x][j];

      terrains[x][y] = -row_sum;
      x++; // @Note: Visited row x_th once.
    }
    else if (hint == dir::right)
    {
      ll col_sum = 0;
      for (int i = 0; i < rows; i++)
        col_sum += terrains[i][y];

      terrains[x][y] = -col_sum;
      y++; // @Note: Visited col y_th once.
    }
  }

  ll final_row_sum = 0L;
  for (int j = 0; j < cols; j++)
    final_row_sum += terrains[rows - 1][j];
  terrains[rows - 1][cols - 1] = -final_row_sum;

  ranges::for_each(terrains, [](const auto &t) { cout << t << "\n"; });
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
