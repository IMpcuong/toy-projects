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

const char _O = '(';
const char _C = ')';

// @Docs: https://codeforces.com/blog/entry/154371

void solve()
{
  auto str_len = nxt<int>();
  auto op = nxt<int>();
  auto bracket_str = nxt<string>();
  assert(str_len == sza(bracket_str));

#if 0
  // @Note: An irrelevant approach but effective when coming to longest valid sub-seq at `i`.
  vector<int> maybe_l;
  maybe_l.reserve(str_len);
  int valid_l = str_len + 1;
  int valid_r = -1;
  pii dp = {valid_l, valid_r};
  for (int i = 0; i < str_len; i++)
  {
    auto cur = bracket_str[i];
    if (cur == _O)
    {
      maybe_l.emplace_back(i);
      continue;
    }

    int open_cnt = sza(maybe_l);
    if (cur == _C)
    {
      if (open_cnt == 0)
        continue;

      valid_r = i;
      valid_l = min(valid_l, maybe_l.back());
      maybe_l.pop_back();
    }
    int l = valid_l;
    int m = dp.second;
    int r = valid_r;

    dp = {valid_l, valid_r};
  }
#endif

  vector<int> pref_open_sums(str_len + 1, 0);
  vector<int> pref_close_sums(str_len + 1, 0);
  for (int i = 0; i < str_len; i++)
  {
    pref_open_sums[i + 1]  = pref_open_sums[i] + (bracket_str[i] == _O);
    pref_close_sums[i + 1] = pref_close_sums[i] + (bracket_str[i] == _C);
  }
  int close_quan = pref_close_sums[str_len];

  int optimal_pos = str_len;
  for (int i = 0; i < str_len; i++)
  {
    int cur_score = pref_open_sums[i] + (close_quan - pref_close_sums[i]);
    int min_score = pref_open_sums[optimal_pos] + (close_quan - pref_close_sums[optimal_pos]);
    if (cur_score < min_score)
      optimal_pos = i;
  }

  string removed(str_len, '0');
  for (int l = 0; l < optimal_pos; l++)
  {
    if (op && bracket_str[l] == _O)
    {
      removed[l] = '1';
      op--;
    }
  }
  for (int r = optimal_pos; r < str_len; r++)
  {
    if (op && bracket_str[r] == _C)
    {
      removed[r] = '1';
      op--;
    }
  }

  println(removed);
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
