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
    os << sep << x, sep = "";
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

const string _L = "L";
const string _R = "R";

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
  deque<int> dq(n);
  generate(all(dq), nxt<int>);

  if (n == 1)
  {
    println(n);
    println(_L);
    return;
  }

  // @Note: n >= 2.
  stack<pair<int, string>> st;
  int l_val = dq.front();
  int r_val = dq.back();
  if (l_val < r_val)
  {
    st.push(pair(l_val, _L));
    dq.pop_front();
  }
  else
  {
    st.push(pair(r_val, _R));;
    dq.pop_back();
  }

  while (!dq.empty())
  {
    l_val = dq.front();
    r_val = dq.back();
    int summit = st.top().first;
    if (summit >= l_val && summit >= r_val)
      break;

    int min_lr = min(l_val, r_val);
    if (min_lr < summit)
      min_lr = max(l_val, r_val);

    if (min_lr == l_val)
    {
      st.push(pair(min_lr, _L));
      dq.pop_front();
    }
    else if (min_lr == r_val)
    {
      st.push(pair(min_lr, _R));
      dq.pop_back();
    }
  }

  if (st.size() == n + 1)
    st.pop();

  int ops = sza(st);
  vector<string> ans(ops);
  while (!st.empty())
  {
    ans.emplace_back(st.top().second);
    st.pop();
  }
  ranges::reverse(ans);
  println(ops);
  cout << ans << "\n";
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.exceptions(ios::badbit | ios::failbit);
  cin.tie(0);
  cout.tie(0);

  int tc = 1;
  // cin >> tc;
  for (int t = 1; t <= tc; t++)
  {
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
