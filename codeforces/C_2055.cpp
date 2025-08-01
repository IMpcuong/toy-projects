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
  auto rows = nxt<int>();
  auto cols = nxt<int>();

  //
  // @Note:
  //  + tampered_path.size()     = rows + cols - 1
  //  + tampered_path.begin_cell = {0, 0}
  //  + tampered_path.end_cell   = {rows - 1, cols - 1}
  //
  auto tampered_path = nxt<string>();

  ll cur_sum_height = 0;
  vector<vector<long>> terrains(rows);
  for (int r = 0; r < rows; r++)
  {
    vector<long> cur_row(cols);
    ranges::generate(cur_row, nxt<long>);

    terrains[r].reserve(cols);
    terrains[r] = cur_row;

    cur_sum_height += accumulate(all(terrains[r]), 0LL);
  }

  // ranges::for_each(terrains, [](const auto &t) { cout << t << "\n"; });

  int tampered_path_len = sza(tampered_path);
  assert(tampered_path_len == rows + cols - 2);
  map<char, ar<int, 2>> dir = {
    {'D', {1, 0}},
    {'R', {0, 1}}
  };
  vector<vector<int>> tampered_coords(rows);
  tampered_coords[0] = {0};
  ar<int, 2> cur_tampered_cell = {0, 0};
  for (const auto &hint : tampered_path)
  {
    cur_tampered_cell[0] += dir[hint][0];
    cur_tampered_cell[1] += dir[hint][1];
    tampered_coords[cur_tampered_cell[0]].emplace_back(cur_tampered_cell[1]);
  }

  long lcm_rc = lcm(rows, cols);
  long coeff = ceildiv(abs(cur_sum_height), lcm_rc);
  long x_choice = coeff * lcm_rc;

  cout << tampered_coords << "\n";
  println(x_choice);
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
    cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
