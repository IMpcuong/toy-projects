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
using ull = unsigned long long;
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
  auto n = nxt<int>(); // n >= 2
  vector<ull> a(n);
  ranges::generate(a, nxt<ull>);

  auto indicate_gcd_of_whole_seq = [&](vector<ull> sub_seq) -> ull
  {
    int sub_seq_sz = sza(sub_seq);
    if (sub_seq_sz == 1)
      return sub_seq[0];

    for (int i = 0; i < sub_seq_sz - 1; i++)
    {
      ull envoy = std::gcd(sub_seq[i], sub_seq[i + 1]);
      sub_seq[i + 1] = envoy;
    }

    return sub_seq[sub_seq_sz - 1];
  };

  vector<ull> odd_idx_seq;
  odd_idx_seq.reserve(n / 2 + 1);
  vector<ull> even_idx_seq;
  even_idx_seq.reserve(n / 2 + 1);
  for (int i = 0; i < n; i++)
  {
    if (i & 1)
    {
      odd_idx_seq.emplace_back(a[i]);
      continue;
    }
    even_idx_seq.emplace_back(a[i]);
  }

  ull maybe_odd_seq_gcd  = indicate_gcd_of_whole_seq(odd_idx_seq);
  ull maybe_even_seq_gcd = indicate_gcd_of_whole_seq(even_idx_seq);

  bool can_choose_odd = maybe_odd_seq_gcd != 1;
  bool can_choose_even = maybe_even_seq_gcd != 1;
  for (int i = 0; i < n; i++)
  {
    if (i & 1)
    {
      can_choose_even &= (a[i] % maybe_even_seq_gcd || a[i] < maybe_even_seq_gcd);
      continue;
    }
    can_choose_odd &= (a[i] % maybe_odd_seq_gcd || a[i] < maybe_odd_seq_gcd);
  }


  if (can_choose_odd && can_choose_even)
    println(max(maybe_odd_seq_gcd, maybe_even_seq_gcd));
  else if (can_choose_odd)
    println(maybe_odd_seq_gcd);
  else if (can_choose_even)
    println(maybe_even_seq_gcd);
  else
    println(0);
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
