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

const char *_D = "DRAW";

void solve()
{
  const int sz = 3;
  ar<ar<char, sz>, sz> board;
  for (int i = 0; i < sz; i++)
    ranges::generate(board[i], nxt<char>);

  auto board_rev = board;
  for (int i = 0; i < sz; i++)
    ranges::reverse(board_rev[i]);

  vector<set<char>> rows(sz);
  vector<set<char>> cols(sz);

  set<char> diag1;
  set<char> diag2;

  for (int i = 0; i < sz; i++)
  {
    for (int j = 0; j < sz; j++)
    {
      char cell = board[i][j];
      rows[i].emplace(cell);
      cols[j].emplace(cell);

      if (i == j)
      {
        diag1.emplace(cell);
        diag2.emplace(board_rev[i][j]);
      }
    }
  }

  if (sza(diag1) == 1)
  {
    char chr = *diag1.begin();
    if (chr != '.')
    {
      println(chr);
      return;
    }
  }
  if (sza(diag2) == 1)
  {
    char chr = *diag2.begin();
    if (chr != '.')
    {
      println(chr);
      return;
    }
  }

  for (const auto &row : rows)
  {
    if (sza(row) != 1)
      continue;

    char chr = *row.begin();
    if (chr != '.')
    {
      println(chr);
      return;
    }
  }
  for (const auto &col : cols)
  {
    if (sza(col) != 1)
      continue;

    char chr = *col.begin();
    if (chr != '.')
    {
      println(chr);
      return;
    }
  }

  println(_D);
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
