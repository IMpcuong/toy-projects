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
  string sep;
  for (const T &x : v)
    os << sep << x, sep = " ";
  return os;
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

void solve()
{
  auto n = nxt<int>();

  //
  // @Hack:
  //  We can predict the final form of the vector b after performing
  //  any amount of computations by evaluating 2 school of thoughts:
  //    + Ascending sequentially := [0, 1, 2, 3, 4, 5, 6] --> FAILED.
  //    + Alternately increase and decrease := [0, 5, 1, 4, 2, 3] --> PASSED.
  //
  vector<int> transformed(n); // transformed = {0, 5, 1, 4, 2, 3 | n = 6}.
  for (int i = 0; i < n; i++)
  {
    if (i & 1)
    {
      transformed[i] = (n - 1) - i / 2;
      continue;
    }
    transformed[i] = i / 2;
  }

  //
  // @Note:
  //  + Exp:
  //    + n = 6
  //    + ans = [6, ...]
  //    + x = ans[1] = ? <=> (ans[0] + x) MOD n = transformed[1]
  //  + Generalize:
  //    ((ans[0] + ... + ans[i - 1]) + x) MOD n = transformed[i]
  //    <=> (ans[0] + ... + ans[i - 1]) + x = transformed[i] + n
  //    <=> pref_sum + x = transformed[i] + n
  //    <=> x = transformed[i] + n - pref_sum
  //  + Wanted: x < n <=> x = x % n
  //
  vector<int> ans(n);
  ans[0] = n;
  int pref_sum = ans[0];
  for (int i = 1; i < n; i++)
  {
    ans[i] = (transformed[i] + n - pref_sum) % n;
    pref_sum += ans[i];
    pref_sum %= n;
  }

  set<int> set_ans(all(ans));
  if (sza(set_ans) < sza(ans))
  {
    println(-1);
    return;
  }

  cout << ans << "\n";
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
