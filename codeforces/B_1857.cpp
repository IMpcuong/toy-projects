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

void solve()
{
  auto str_num = nxt<string>();
  int digit_quan = sza(str_num);
  ranges::reverse(str_num);
  vector<int> digits;
  digits.reserve(digit_quan);
  for (const auto &digit : str_num)
    digits.emplace_back(digit - '0');
  digits.insert(digits.end(), 0);

  int mark = -1;
  int stock = 0;
  for (int k = 1; k <= digit_quan; k++)
  {
    int cur  = digits[k];
    int prev = digits[k - 1];
    if (stock)
    {
      if (cur < 9)
      {
        cur += stock;
        stock = 0;
      }
      if (cur == 9)
        cur = 0;

      mark = max(mark, k);
    }
    if (prev >= 5)
    {
      if (cur < 9)
        cur++;
      if (cur == 9)
      {
        cur = 0;
        stock = 1;
      }

      mark = max(mark, k);
    }

    digits[k] = cur;
  }
  for (int i = 0; i < mark; i++)
    digits[i] = 0;
  ranges::reverse(digits);

  string ans = "";
  ranges::for_each(digits, [&](const auto &d) { ans += to_string(d); });
  if (ans[0] == '0')
    ans.erase(ans.begin());
  println(ans);
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
