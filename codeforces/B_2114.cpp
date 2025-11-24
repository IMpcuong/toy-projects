#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -g -Wall -Wextra -fsanitize=address -O3 tmpl.cpp -o out

using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

template <typename ...Args>
ostream &operator<<(ostream &os, const tuple<Args...> &t)
{
  os << '{';
  string sep;
  apply([&](auto &&...args) { ((os << sep << args, sep = ", "), ...); }, t);
  return os << '}';
}

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
concept Input_Streamable_Type = requires(T stdin_data)
{
  cin >> stdin_data;
};

template <Input_Streamable_Type IST>
inline IST nxt()
{
  IST x;
  cin >> x;
  return x;
}

const char *_Y = "YES";
const char *_N = "NO";

void solve()
{
  auto len = nxt<int>(); // len % 2 := 0
  auto limit = nxt<int>();
  auto bin_s = nxt<string>();

  int diff_cnt = 0;
  ar<int, 2> pair_cnt = {0, 0};
  for (int i = 0; i < len / 2; i++)
  {
    int palindrome = (len - 1) - i;
    if (bin_s[i] != bin_s[palindrome])
    {
      diff_cnt++;
      if (diff_cnt == 2 && limit >= 2)
      {
        limit -= 2;
        diff_cnt = 0;
      }
      continue;
    }

    if (limit > 0)
      limit--;
    else if (limit == 0)
      pair_cnt[bin_s[i] - '0']++;
  }

  if (limit == 0)
  {
    if (pair_cnt[0] == pair_cnt[1])
      println(_Y);
    else
      println(_N);
    return;
  }

  int remain_pair = abs(pair_cnt[0] - pair_cnt[1]);
  if (limit == remain_pair)
    println(_Y);
  else
    println(_N);
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
