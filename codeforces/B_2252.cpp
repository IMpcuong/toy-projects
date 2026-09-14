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

void solve()
{
  auto n = nxt<int>();
  auto bin_str = nxt<string>();

  int one_quan = ranges::count(bin_str, '1');
  int zero_quan = n - one_quan;

  int excess_one_quan = 0;
  int excess_zero_quan = 0;
  for (int i = 0; i < n; i++)
  {
    char pin = bin_str[i];
    int j = i;
    while (j < n && bin_str[j] == pin && ++j);
    if (j > i)
    {
      if (pin == '1')
        excess_one_quan += j - i - 1;
      else
        excess_zero_quan += j - i - 1;

      i = j - 1;
    }
  }

  if (excess_one_quan == 0 && excess_zero_quan == 0)
  {
    println(0);
    return;
  }

  int total_deletion = excess_one_quan + excess_zero_quan;
  int delta = abs(excess_one_quan - excess_zero_quan);
  if (delta <= 1)
  {
    println(total_deletion);
    return;
  }

  int compensation = delta - 1;
  if (excess_one_quan > excess_zero_quan)
  {
    int remaining_one = one_quan - excess_one_quan;
    int remaining_zero = zero_quan - excess_zero_quan;
    if (remaining_zero < compensation)
    {
      println(-1);
    }
    else
    {
      remaining_zero -= compensation;
      if (abs(remaining_one - remaining_zero) > 1)
        println(-1);
      else
        println(total_deletion + compensation);
    }
  }
  else
  {
    int remaining_zero = zero_quan - excess_zero_quan;
    int remaining_one = one_quan - excess_one_quan;
    if (remaining_one < compensation)
    {
      println(-1);
    }
    else
    {
      remaining_one -= compensation;
      if (abs(remaining_one - remaining_zero) > 1)
        println(-1);
      else
        println(total_deletion + compensation);
    }
  }
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
