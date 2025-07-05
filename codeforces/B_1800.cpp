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
  auto n = nxt<int>();
  auto ops = nxt<int>();
  auto s = nxt<string>();

#define custom_lower(ch) static_cast<char>(tolower(static_cast<unsigned char>(ch)))

  const int _alphabet = 26;
  vector<vector<int>> cases_by_char(_alphabet);
  for (const auto &chr : s)
  {
    char lower_chr = custom_lower(chr);
    if (chr - lower_chr)
    {
      cases_by_char[lower_chr - 'a'].emplace_back(1);
      continue;
    }
    cases_by_char[lower_chr - 'a'].emplace_back(0);
  }

  int ans = 0;
  for (int i = 0; i < _alphabet; i++)
  {
    int cur_char_quan = sza(cases_by_char[i]);
    int left_with_same_type_quan = cur_char_quan;
    vector<bool> visited(cur_char_quan, false);
    int k = 0;
    for (int j = 0; j < cur_char_quan - 1; j++)
    {
      if (visited[j])
        continue;

      char curr_case = cases_by_char[i][j];
      while (k < cur_char_quan)
      {
        if (curr_case != cases_by_char[i][k] && !visited[k])
        {
          ans++;
          visited[j] = true;
          visited[k] = true;
          left_with_same_type_quan -= 2;
          break;
        }
        k++;
      }
    }
    if (!ops)
      continue;

    int extra_pair_cnt = min(ops, left_with_same_type_quan / 2);
    ans += extra_pair_cnt;
    ops -= extra_pair_cnt;
  }

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
