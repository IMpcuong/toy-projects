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
  auto f_num = nxt<string>();
  auto sum = nxt<string>();

  int f_len = sza(f_num);
  int sum_len = sza(sum);

  ranges::reverse(f_num);
  ranges::reverse(sum);

  int pref_len = sum_len - f_len;
  while (pref_len)
  {
    f_num += '0';
    pref_len--;
  }

  vector<int> s_num;
  int j = 0;
  for (int i = 0; i < sum_len; i++)
  {
    if (i == sum_len - 1 && j < f_len - 1)
    {
      println(-1);
      return;
    }

    int sum_digit = sum[i] - '0';
    int f_digit = f_num[j] - '0';
    if (sum_digit >= f_digit)
    {
      int s_digit = sum_digit - f_digit;
      s_num.push_back(s_digit);
      if (j < sum_len)
        j++;
      continue;
    }

    if (i < sum_len)
    {
      i++;
      sum_digit += 10 * (sum[i] - '0');
      int s_digit = sum_digit - f_digit;
      if (s_digit > 9)
      {
        println(-1);
        return;
      }
      s_num.push_back(s_digit);
      if (j < sum_len)
        j++;
    }
  }

  ranges::reverse(s_num);
  string ans;
  for (const auto &digit : s_num)
  {
    if (ans.empty() && digit == 0)
      continue;
    ans += to_string(digit);
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
