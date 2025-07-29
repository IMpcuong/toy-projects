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

const char *_B = "Bodya";
const char *_S = "Sasha";
const char *_D = "Draw";

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
  ar<int, 4> params;
  ranges::generate(params, nxt<ll>);

  auto &[n, turns, start_B, start_S] = params;
  vector<int> permu(n);
  ranges::generate(permu, nxt<int>);
  vector<ll> scores(n);
  ranges::generate(scores, nxt<ll>);

  ll max_score = *ranges::max_element(scores);

  vector<ll> route_B_to_max_score;
  route_B_to_max_score.reserve(n);
  vector<ll> route_S_to_max_score;
  route_S_to_max_score.reserve(n);

  auto collect_scores_until_reach_max = [&](ll start_pos, vector<ll> &route) -> vector<ll>
  {
    ll cur_score = scores[start_pos - 1];
    route.emplace_back(cur_score);

    int start_pos_freeze = start_pos;
    while (cur_score < max_score)
    {
      int nxt_pos = permu[start_pos - 1];
      if (nxt_pos == start_pos_freeze)
        break;

      cur_score = scores[nxt_pos - 1];
      route.emplace_back(cur_score);
      if (cur_score == max_score)
        break;

      start_pos = nxt_pos;
    }

    route.shrink_to_fit();
    return route;
  };

  collect_scores_until_reach_max(start_B, route_B_to_max_score);
  collect_scores_until_reach_max(start_S, route_S_to_max_score);

  // cout << route_B_to_max_score << "\n";
  // cout << route_S_to_max_score << "\n";

  int route_B_len = sza(route_B_to_max_score);
  route_B_len = turns > route_B_len ? route_B_len : turns;
  int route_S_len = sza(route_S_to_max_score);
  route_S_len = turns > route_S_len ? route_S_len : turns;

  vector<ll> pref_sums_B = {0};
  pref_sums_B.reserve(route_B_len + 1);
  for (const auto &score : route_B_to_max_score)
    pref_sums_B.emplace_back(pref_sums_B.back() + score);

  vector<ll> pref_sums_S = {0};
  pref_sums_S.reserve(route_S_len + 1);
  for (const auto &score : route_S_to_max_score)
    pref_sums_S.emplace_back(pref_sums_S.back() + score);

  ll final_B_score = -1;
  for (int i = 0; i < route_B_len; i++)
    final_B_score = max(final_B_score, pref_sums_B[i] + (turns - i) * route_B_to_max_score[i]);

  ll final_S_score = -1;
  for (int i = 0; i < route_S_len; i++)
    final_S_score = max(final_S_score, pref_sums_S[i] + (turns - i) * route_S_to_max_score[i]);

  if (final_B_score == final_S_score)
    println(_D);
  else if (final_B_score > final_S_score)
    println(_B);
  else
    println(_S);
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
