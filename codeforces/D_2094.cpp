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

const char *_Y = "YES";
const char *_N = "NO";

void solve()
{
  auto orig = nxt<string>();
  auto real = nxt<string>();

  int orig_sz = sza(orig);
  int real_sz = sza(real);

  map<pair<char, int>, int> omap;
  int j = 0;
  int inc = 0;
  for (int i = 0; i < orig_sz; i++)
  {
    while (orig[i] == orig[j] && j < orig_sz && ++j);
    omap[pair{orig[i], inc}] = j - i;
    inc++;
    i = j - 1;
  }

  map<pair<char, int>, int> rmap;
  j = 0;
  inc = 0;
  for (int i = 0; i < real_sz; i++)
  {
    while (real[i] == real[j] && j < real_sz && ++j);
    rmap[pair{real[i], inc}] = j - i;
    inc++;
    i = j - 1;
  }

  if (omap.size() != rmap.size())
  {
    println(_N);
    return;
  }
  for (auto oit = omap.begin(), rit = rmap.begin();
       oit != omap.end() && rit != rmap.end(); oit++, rit++)
  {
    if (oit->first.first != rit->first.first ||
        oit->first.second != rit->first.second)
    {
      println(_N);
      return;
    }
    if (oit->second > rit->second || 2 * oit->second < rit->second)
    {
      println(_N);
      return;
    }
  }

  println(_Y);
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
