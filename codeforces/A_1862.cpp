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
  auto rows = nxt<int>();
  auto cols = nxt<int>();
  vector<string> mat(rows);
  for (int i = 0; i < rows; i++)
    mat[i] = nxt<string>();

  const string _seq = "vika";

  map<char, set<int>> locs_by_col;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      char chr = mat[i][j];
      for (const auto &target : _seq)
      {
        if (chr != target)
          continue;

        locs_by_col[chr].emplace(j);
      }
    }
  }

  // for (const auto &[chr, locs] : locs_by_col)
  //   cout << chr << ": " << locs << "\n";

  int last_valid_idx = -1;
  bool can_form_seq = true;
  for (const auto &chr : _seq)
  {
    if (sza(locs_by_col[chr]) == 0)
    {
      can_form_seq = false;
      break;
    }

    for (const auto &idx : locs_by_col[chr])
    {
      bool appendable = idx > last_valid_idx;
      if (appendable)
      {
        last_valid_idx = idx;
        can_form_seq = true;
        break;
      }
      can_form_seq &= appendable;
    }

    if (!can_form_seq)
      break;
  }

  println(can_form_seq ? _Y : _N);
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
