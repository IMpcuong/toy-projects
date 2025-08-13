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

void solve()
{
  auto n = nxt<int>();
  auto prob_cnt = nxt<int>();
  auto duration = nxt<long>();

  vector<vector<long>> solved_by(n, vector<long>(prob_cnt));
  for (int i = 0; i < n; i++)
  {
    ranges::generate(solved_by[i], nxt<long>);
    ranges::sort(solved_by[i]);
  }

  struct candidate
  {
    int idx;
    int score;
    ll penalty;
  };
  vector<candidate> ranks(n);
  for (int i = 0; i < n; i++)
  {
    ranks[i].idx = i + 1;

    ll time_to_solve = 0;
    ll penalty_val = 0;
    for (int prob = 0; prob < prob_cnt; prob++)
    {
      time_to_solve += solved_by[i][prob];
      if (time_to_solve > duration)
        break;

      ranks[i].score++;
      if (time_to_solve <= duration)
        penalty_val += time_to_solve;
    }
    ranks[i].penalty = penalty_val;
  }
  ranges::sort(ranks,
      [](const auto &f, const auto &s)
      {
        if (f.score == s.score)
        {
          if (f.penalty == s.penalty)
            return f.idx < s.idx;
          return f.penalty < s.penalty;
        }
        return f.score > s.score;
      });

  // ranges::for_each(ranks, [](const auto &r) { println(r.idx, r.score, r.penalty); });
  for (int i = 0; i < n; i++)
  {
    if (ranks[i].idx == 1)
    {
      println(i + 1);
      return;
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
