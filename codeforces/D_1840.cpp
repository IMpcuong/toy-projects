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

pair<ll, ll> cal_last_two_chunks_delta(const vector<ll> &vec,
    const int &l2, const int &r2)
{
  int n = sza(vec);
  int l3 = r2 + 1;
  int r3 = n - 1;

  // println(l2, r2, "|", l3, r3);

  ll avg2 = (vec[l2] + vec[r2]) / 2;
  ll avg3 = (vec[l3] + vec[r3]) / 2;

  // println(avg2, avg3);

  ll cur_max_delta2 = max(abs(avg2 - vec[l2]), abs(avg2 - vec[r2]));
  ll cur_max_delta3 = max(abs(avg3 - vec[l3]), abs(avg3 - vec[r3]));

  return pair(cur_max_delta2, cur_max_delta3);
}

void solve()
{
  auto n = nxt<int>();
  vector<ll> a(n);
  generate(all(a), nxt<ll>);
  ranges::sort(a);

  if (n == 1 || n == 2 || n == 3)
  {
    println(0);
    return;
  }

  auto bin_search = [&](auto &&l, auto &&r) -> int
  {
    double mid_val = ((double)a[l] + (double)a[r]) / 2;

    while (l <= r)
    {
      int m = (l + r) / 2;
      if (a[m] < mid_val)
        l = m + 1;
      else if (a[m] > mid_val)
        r = m - 1;
      else
        return m;
    }

    // @Note: If `mid_val` doesn't present in `a`.
    //  + a[r] <= mid_val && a[r] is closest to `mid_val`.
    //  + a[l] >= mid_val && a[l] is closest to `mid_val`.

    ll delta_lt = mid_val - a[r];
    ll delta_gt = a[l] - mid_val;

    return delta_lt < delta_gt ? r : l;
  };

  ll min_delta = INF;
  for (int i = 0; i < n - 2; i++)
  {
    int l1 = 0;
    int r1 = i;
    ll avg1 = (a[l1] + a[r1]) / 2;
    ll cur_max_delta1 = max(abs(avg1 - a[l1]), abs(avg1 - a[r1]));

    int l2 = i + 1;
    int r2 = bin_search(i + 1, n - 1);
    if (l2 > r2)
      break;

    pair<ll, ll> p1 = cal_last_two_chunks_delta(a, l2, r2);
    pair<ll, ll> p2 = cal_last_two_chunks_delta(a, l2, r2 - 1);

    ll cur_max_delta2 = p1.first;
    ll cur_max_delta3 = p1.second;
    ll cur_max_delta_try1 = max(max(cur_max_delta1, cur_max_delta2), cur_max_delta3);

    cur_max_delta2 = p2.first;
    cur_max_delta3 = p2.second;
    ll cur_max_delta_try2 = max(max(cur_max_delta1, cur_max_delta2), cur_max_delta3);

    // println(cur_max_delta1, cur_max_delta2, cur_max_delta3);

    ll cur_max_delta = min(cur_max_delta_try1, cur_max_delta_try2);
    min_delta = min(min_delta, cur_max_delta);
  }

  println(min_delta);
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
