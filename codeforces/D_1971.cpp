#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -Wall -Wextra -O2 tmpl.cpp -o out -v

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
  ((std::cout << (end ? (end = false, "") : " ") << args), ...);
}

template <typename... Args>
void println(const Args &...args)
{
  bool end = true;
  ((std::cout << (end ? (end = false, "") : " ") << args), ...) << "\n";
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
#define us unsigned short
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

us solve()
{
  // @Note:
  //  + bin_str := 1 block (original)
  //  + bin_str.sort() := [blocks_0s=0...0][bridge=0...1 <= 1 block][blocks_1s=1...1]
  string bin_str;
  cin >> bin_str;

  //
  // @Idea: blocks (minimum) = {blocks_0s + blocks_1s - bridge | bridge <= 1}
  //

  us blocks = 1;
  us bridge = 0;
  for (int i = 0; i < sza(bin_str) - 1; i++)
  {
    char chr_cur = bin_str[i];
    char chr_next = bin_str[i + 1];
    if (chr_cur != chr_next)
      // [...01|10...] (1 block) -> split: blocks_0s += 1 || blocks_1s += 1.
      blocks += 1;
    bridge |= (chr_cur == '0' && chr_next == '1');
  }
  return blocks - bridge;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++)
  {
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    println(solve());
  }
}
