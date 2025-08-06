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
  vector<int> permu(n);
  ranges::generate(permu, nxt<int>);

  if (n == 1 || n == 2)
  {
    ranges::reverse(permu);
    cout << permu << "\n";
    return;
  }

  if (n == permu[n - 1])
  {
    int mark_pos = n - 1;
    for (int i = mark_pos - 1; i >= 0; i--)
    {
      int cur = permu[i];
      if (cur > permu[0])
        continue;

      mark_pos = i;
      break;
    }

    vector<int> ans = vector(permu.begin() + mark_pos + 1, permu.end());
    ranges::reverse(ans);
    ans.reserve(n);
    for (int i = 0; i <= mark_pos; i++)
      ans.emplace_back(permu[i]);

    permu = ans;
  }
  else if (n == permu[0])
  {
    int mark_value = n - 1;
    int mark_pos = 0;
    for (int i = 1; i < n; i++)
    {
      if (permu[i] == mark_value)
      {
        mark_pos = i;
        break;
      }
    }

    vector<int> ans = vector(permu.begin() + mark_pos, permu.end());
    ans.reserve(n);
    if (mark_pos < n - 1)
    {
      ans.emplace_back(permu[mark_pos - 1]);
      mark_pos--;
    }
    for (int i = 0; i < mark_pos; i++)
      ans.emplace_back(permu[i]);

    permu = ans;
  }
  else
  {
    int mark_value = n;
    int mark_pos = 0;
    for (int i = 1; i < n - 1; i++)
    {
      if (permu[i] == mark_value)
      {
        mark_pos = i;
        break;
      }
    }

    int reverse_range = 0;
    for (int i = mark_pos - 1; i >= 0; i--)
    {
      int cur = permu[i];
      if (cur > permu[0])
      {
        reverse_range++;
        continue;
      }

      break;
    }

    vector<int> ans = vector(permu.begin() + mark_pos, permu.end());
    ans.reserve(n);
    if (reverse_range == 0)
    {
      ranges::reverse(permu.begin(), permu.begin() + mark_pos);
    }
    else
    {
      for (int i = mark_pos - 1; i > mark_pos - 1 - reverse_range; i--)
        ans.emplace_back(permu[i]);
    }
    ans.insert(ans.end(), permu.begin(), permu.begin() + mark_pos - reverse_range);

    permu = ans;
  }

  cout << permu << "\n";
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
