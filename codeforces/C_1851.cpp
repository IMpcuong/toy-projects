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

const string _Y = "YES";
const string _N = "NO";

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

bool solve()
{
  auto n = nxt<long>();
  auto k = nxt<long>();
  vector<long> a(n);
  generate(all(a), nxt<long>);

  long m = *max_element(all(a));
  vector<long> freq(m + 1, 0);
  for (long i = 0; i < n; i++)
    freq[a[i]]++;

  if (freq[a[n - 1]] < k || freq[a[0]] < k)
    return false;

  if (a[0] == a[n - 1])
    return true;

  long f = *ranges::find_if(a, [&](const long &v) { return v == a[0]; });
  long l = *ranges::find_if(a, [&](const long &v) { return v == a[n - 1]; });
  long f_freq = 0;
  long l_freq = 0;
  for (long i = 0; i < n; i++)
  {
    if (a[i] == a[0])
    {
      f_freq++;
      if (f_freq == k)
        f = i;
    }
    if (a[i] == a[n - 1])
    {
      l_freq++;
      if (freq[a[n - 1]] - l_freq == k - 1)
        l = i;
    }
  }
  // println(f, l);
  if (f > l)
    return false;

  return true;
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
    solve() ? println(_Y) : println(_N);
  }
}
