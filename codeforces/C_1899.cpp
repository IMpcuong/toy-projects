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

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

void solve()
{
  auto n = nxt<long>();
  vector<int> a(n);
  generate(all(a), nxt<int>);

  vector<long> inc_sum = {0};
  inc_sum.reserve(n + 1);
  for (const auto &v : a)
    inc_sum.emplace_back(inc_sum.back() + v);

  vector<pair<int, int>> range_pairs;
  range_pairs.reserve(n);
  int start = 0;
  int end = 0;
  for (int i = 1; i < n; i++)
  {
    int prev = a[i - 1];
    int cur = a[i];
    if ((cur + prev) & 1)
    {
      end = i;
    }
    else
    {
      if (end > start)
        range_pairs.emplace_back(start, end);
      start = i;
      end = i;
    }
  }
  if (end > start)
    range_pairs.emplace_back(start, end);
  if (end == n - 1 && start == n - 1)
    for (int i = 0; i < n; i++)
      range_pairs.emplace_back(i, i);
  range_pairs.shrink_to_fit();

  // cout << range_pairs << "\n";

  long max_sum = -INF;
  for (auto const &p : range_pairs)
  {
    long cur_sum = 0;
    for (int i = p.first; i <= p.second; i++)
    {
      cur_sum = max(cur_sum + long(a[i]), long(a[i]));
      max_sum = max(max_sum, cur_sum);
      println(cur_sum, max_sum);
    }
  }

  println(max_sum);
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
