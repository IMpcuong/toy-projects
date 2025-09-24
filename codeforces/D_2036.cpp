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

const string _TARGET = "1543";
const int _TARGET_SZ = sza(_TARGET);

void solve()
{
  auto rows = nxt<int>(); // rows % 2 := 0
  auto cols = nxt<int>(); // cols % 2 := 0
  vector<string> mat(rows);
  for (int i = 0; i < rows; i++)
    mat[i] = nxt<string>();

  int l_quan = min(rows, cols) >> 1;
  vector<deque<char>> layers(l_quan);
  for (int i = 0; i < rows - 1; i++)
  {
    for (int f = 0; f < i && f < l_quan; f++)
      layers[f].emplace_front(mat[i][f]);

    if (i < l_quan)
      for (int j = i; j < cols - i; j++)
        layers[i].emplace_back(mat[i][j]);

    for (int b = cols - i; b < cols; b++)
    {
      int lid = cols - b - 1;
      if (0 <= lid && lid < l_quan)
        layers[lid].emplace_back(mat[i][b]);
    }
  }
  for (int j = 0; j < cols; j++)
    layers[0].emplace_front(mat[rows - 1][j]);

  // ranges::for_each(layers, [](const auto &r) { cout << r << "\n"; });

  int app_cnt = 0;
  for (const auto &layer : layers)
  {
    int layer_len = sza(layer);
    for (int i = 0; i < layer_len; i++)
    {
      char digit = layer[i];
      if (digit == _TARGET[0])
      {
        string maybe_match(1, digit);
        for (int j = 1; j < _TARGET_SZ; j++)
          maybe_match += layer[(i + j) % layer_len];

        app_cnt += strncmp(maybe_match.c_str(), _TARGET.c_str(), _TARGET_SZ) == 0;
      }
    }
  }

  println(app_cnt);
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
