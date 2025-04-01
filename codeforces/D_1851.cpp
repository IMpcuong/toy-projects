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

const string _Y = "YES";
const string _N = "NO";

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

template <typename T>
inline T nxt()
{
  T x;
  cin >> x;
  return x;
}

bool solve()
{
  auto n = nxt<ll>();
  vector<ll> pref_sums(n - 1);
  generate(all(pref_sums), nxt<ll>);

  ll last_pref_sum = (n + 1) * n / 2;

  auto is_permu_n = [&](const vector<ll> &v) -> bool
  {
    auto v_len = v.size();
    if (v_len != n)
      return false;

    for (size_t i = 0; i < v_len; i++)
      if (v[i] <= 0 || v[i] > n)
        return false;

    set<ll> v_set = set(all(v));
    return v_set.size() == v_len;
  };

  auto conv_to_permu_from = [&](const vector<ll> &psum) -> vector<ll>
  {
    vector<ll> permu(n);
    permu[0] = psum[0]; // @Note: psum.size() >= 2.
    for (int i = 1; i < n; ++i)
      permu[i] = psum[i] - psum[i - 1];

    return permu;
  };

  if (pref_sums.back() != last_pref_sum)
  {
    pref_sums.emplace_back(last_pref_sum);
    // cout << pref_sums << "\n";
    auto full_permu = conv_to_permu_from(pref_sums);
    // cout << full_permu << "\n";
    if (is_permu_n(full_permu))
      return true;
    else
      return false;
  }

  map<ll, int> freq;
  freq[pref_sums[0]]++;
  for (int i = 1; i < n - 1; ++i)
    freq[pref_sums[i] - pref_sums[i - 1]]++;

  // cout << freq << "\n";

  int cnt_dup = 0;
  for (const auto &p : freq)
  {
    if (p.second > 2)
      return false;
    if (p.second == 2)
      cnt_dup++;
  }
  if (cnt_dup > 1)
    return false;

  int cnt_num_left = 0;
  for (int i = 1; i <= n; i++)
  {
    if (freq[i] == 0)
      cnt_num_left++;
  }
  if (cnt_num_left != 2)
    return false;

  return true;
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
    solve() ? println(_Y) : println(_N);
  }
}
