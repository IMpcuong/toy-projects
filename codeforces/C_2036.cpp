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

const string _TARGET = "1100";
const char *_Y       = "YES";
const char *_N       = "NO";

void solve()
{
  auto bin_str = nxt<string>();
  auto q_quan = nxt<int>();

  vector<pair<int, char>> queries(q_quan);
  for (int q = 0; q < q_quan; q++)
  {
    queries[q].first  = nxt<int>() - 1;
    queries[q].second = nxt<char>();
  }

  const int target_len = sza(_TARGET);

  int str_sz = sza(bin_str);
  ar<int, 2> cache_interval;
  vector<int> intervals(str_sz - target_len + 1, -1);
  for (int l = 0; l < str_sz - target_len + 1; l++)
  {
    if (bin_str.substr(l, target_len) == _TARGET)
    {
      intervals[l] = l + target_len - 1;
      cache_interval = ar{l, l + target_len - 1};
    }
  }
  int interval_cnt = ranges::count_if(intervals, [](const auto &r) { return r > 0; });

  if (interval_cnt > 1)
  {
    int q_quan_rep = q_quan;
    while (q_quan_rep)
    {
      println(_Y);
      q_quan_rep--;
    }

    return;
  }

  if (interval_cnt == 0)
  {
    bool contain_target = false;
    for (const auto &q : queries)
    {
      int pos = q.first;
      char alt = q.second;
      char hold = bin_str[pos];
      if (hold == alt)
      {
        println(_N);
        continue;
      }

      int lower = max(0, pos - target_len + 1);
      bin_str[pos] = alt;
      {
        for (int l = lower; l <= pos; l++)
        {
          if (l + target_len >= str_sz)
            break;
          contain_target |= (bin_str.substr(l, target_len) == _TARGET);
        }
        if (contain_target)
          println(_Y);
        else
          println(_N);
      }
      bin_str[pos] = hold;
    }
  }

  if (interval_cnt == 1)
  {
    for (const auto &q : queries)
    {
      int pos = q.first;
      char alt = q.second;
      int l = cache_interval[0];
      int r = cache_interval[1];
      // cout << pos << " " << cache_interval << "\n";
      if (pos < l || pos > r)
      {
        println(_Y);
        continue;
      }
      if (bin_str[pos] == alt)
        println(_Y);
      else
        println(_N);
    }
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
