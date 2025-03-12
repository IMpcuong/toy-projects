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
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

constexpr string _Y = "YES";
constexpr string _N = "NO";

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

string solve()
{
  auto len = nxt<int>();
  vector<int> a(len);
  generate(all(a), nxt<int>);

  // ll sum = accumulate(all(a), 0);
  // if (sum % len != 0)
  //   return _N;

  ll sum_odd = 0;
  ll sum_even = 0;
  for (int i = 0; i < len; i++)
  {
    if (i & 1)
      sum_odd += a[i];
    else
      sum_even += a[i];
  }

  int quan_odd = len / 2;
  int quan_even = len / 2;
  if (len & 1)
    quan_even++;

  if (sum_odd % quan_odd != 0 || sum_even % quan_even != 0)
    return _N;
  if (sum_odd / quan_odd != sum_even / quan_even)
    return _N;

  return _Y;
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
    println(solve());
  }
}
