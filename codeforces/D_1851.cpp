#include <algorithm>
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

const int max_n = 1e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e9;
const ld eps = 1e-9;

const string _Y = "YES";
const string _N = "NO";

template <typename t>
inline t nxt()
{
  t x;
  cin >> x;
  return x;
}

void solve()
{
  auto n = nxt<long>();
  long given_len = n - 1;
  vector<ll> a(given_len);
  generate(all(a), nxt<ll>);

  vector<ll> permu(given_len);
  for (long i = given_len; i >= 1; i--)
  {
    ll cur_num = a[i] - a[i - 1];
    permu[i] = cur_num;
  }
  permu[0] = a[0];

  // cout << permu << "\n";

  ll max_num = *max_element(all(permu));
  if (max_num > (n - 1) + (n - 2))
  {
    println(_N);
    return;
  }

  vector<long> freq(n + 1, 0);
  long cnt_greater = 0;
  for (const auto &num : permu)
  {
    if (num > n)
    {
      cnt_greater++;
      continue;
    }
    freq[num]++;
  }
  if (cnt_greater > 1)
  {
    println(_N);
    return;
  }

  long ex_nums = 0;
  long possible_sum = 0;
  for (int i = 1; i < n + 1; i++)
  {
    if (freq[i] > 0)
    {
      ex_nums++;
      continue;
    }
    possible_sum += i;
  }

  long left_nums = n - ex_nums;
  if (possible_sum > n)
  {
    if (possible_sum != max_num)
    {
      println(_N);
      return;
    }
  }
  else if (possible_sum == n)
  {
    if (left_nums > 1)
    {
      println(_N);
      return;
    }
  }
  else
  {
    if (left_nums < 1)
    {
      println(_N);
      return;
    }
  }

  println(_Y);
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
    // cout << "Case #" << t << ": "; // @warn: commenting before submission.
    solve();
  }
}
