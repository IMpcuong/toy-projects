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
#define ceiulliv(n, k) (((n) + (k) - 1) / (k))

using ll = long long;
using ld = long double;
using ull = unsigned long long;
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

ull solve()
{
  auto n = nxt<ull>();
  ull n_copy = n;
  auto s = nxt<int>();

  vector<int> digits;
  digits.reserve(18);
  while (n)
  {
    auto digit = static_cast<int>(n % 10);
    digits.emplace_back(digit);
    n /= 10;
  }
  digits.shrink_to_fit();
  ranges::reverse(digits);

  int cur_digit_sum = accumulate(all(digits), 0);
  if (cur_digit_sum <= s)
    return 0;

  int sum_digit = 0;
  int mark_pos = -1;
  int mark_tmp = -1;
  for (int i = 0; i < sza(digits); i++)
  {
    sum_digit += digits[i];
    if (sum_digit <= s)
      continue;

    if (digits[i] > 0)
      mark_tmp = max(mark_tmp, i);
    mark_pos = max(0, i);
    break;
  }
  mark_pos = digits[mark_pos] == 0 ? mark_tmp : mark_pos;
  mark_pos = mark_pos == 0 ? sza(digits) - 1 : mark_pos;

  ull new_n = 0;
  ull upper = pow(10ULL, sza(digits));
  if ((mark_pos == 0 && sza(digits) == 1) || digits[0] == s)
  {
    new_n = upper;
    return new_n - n_copy;
  }

  sum_digit = accumulate(digits.begin(), digits.begin() + mark_pos + 1, 0);
  for (int j = mark_pos; j > 0; j--)
  {
    sum_digit += 1 - digits[j];
    digits[j] = 0;
    digits[j - 1]++;
    if (sum_digit <= s)
      break;
  }

  if (sum_digit > s)
    new_n = upper;
  else
    for (int k = 0; k < mark_pos; k++)
      new_n += ull(digits[k]) * pow(10ULL, sza(digits) - (k + 1));

  return new_n - n_copy;
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
    println(solve());
  }
}
