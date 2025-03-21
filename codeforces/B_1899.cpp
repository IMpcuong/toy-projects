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
  vector<long> a(n);
  generate(all(a), nxt<long>);

  vector<ll> inc_sum = {0};
  inc_sum.reserve(n + 1);
  for (const auto &v : a)
    inc_sum.emplace_back(inc_sum.back() + v);

  auto cal_max_delta = [&](const long &quan,
                           const long &payload) -> ll
  {
    if (quan == 1)
      return 0;

    ll max_w = 0;
    ll min_w = inc_sum[n];
    for (long id = 0; id < quan; id++)
    {
      ll truck_w = inc_sum[(id + 1) * payload] - inc_sum[id * payload];
      max_w = max(max_w, truck_w);
      min_w = min(min_w, truck_w);
    }

    return max_w - min_w;
  };

  ll max_diff = 0;
  auto upper = static_cast<int>(ceil(sqrt(n)));
  for (int k = 1; k <= upper; k++)
  {
    if (n % k != 0)
      continue;

    long trucks = n / k;
    max_diff = max(max_diff, cal_max_delta(trucks, k));
    if (k != trucks)
      max_diff = max(max_diff, cal_max_delta(k, trucks));
  }

  println(max_diff);
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
