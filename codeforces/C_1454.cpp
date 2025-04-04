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

int solve()
{
  auto n = nxt<int>();
  vector<int> a(n);
  generate(all(a), nxt<int>);

  stack<int> st;
  for (const auto &num : a)
  {
    if (st.empty())
    {
      st.push(num);
      continue;
    }

    if (st.top() == num)
      continue;
    else
      st.push(num);
  }

  vector<int> unq;
  unq.reserve(st.size());
  while (!st.empty())
  {
    int v = st.top();
    st.pop();
    unq.emplace_back(v);
  }

  vector<int> freq(n + 1);
  for (const auto &num : unq)
    freq[num]++;

  if (*max_element(all(freq)) == sza(unq))
    return 0;

  int ops = INF;
  for (int i = 1; i < n + 1; i++)
  {
    if (freq[i] == 0)
      continue;

    if (freq[i] == 1)
    {
      if (i == a.front() || i == a.back())
        ops = min(ops, freq[i]);
      else
        ops = min(ops, freq[i] + 1);

      continue;
    }

    if (i == a.front() && i == a.back())
      ops = min(ops, freq[i] - 1);
    else if (i == a.front() || i == a.back())
      ops = min(ops, freq[i]);
    else
      ops = min(ops, freq[i] + 1);
  }

  return ops;
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
