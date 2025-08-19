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
  auto target = nxt<string>();
  auto set_quan = nxt<int>();
  vector<string> sub_seqs(set_quan);
  ranges::generate(sub_seqs, nxt<string>);

  int target_len = sza(target);
  struct interval
  {
    int belong_to;
    int l;
    int r;

    bool operator<(const interval &other) const
    {
      return this->l < other.l;
    }
  };
  vector<interval> seq_intervals;
  for (int i = 0; i < set_quan; i++)
  {
    string sub = sub_seqs[i];
    int sub_len = sza(sub);
    for (int j = 0; j < target_len - sub_len + 1; j++)
    {
      string sub_from_target = target.substr(j, sub_len);
      if (sub == sub_from_target)
        seq_intervals.emplace_back(interval{i /*belong_to=*/, j /*l=*/, j + sub_len - 1 /*r=*/});
    }
  }
  ranges::sort(seq_intervals, [](const auto &f, const auto &s) { return f < s; });
  if (seq_intervals.empty() || seq_intervals.front().l > 0)
  {
    println(-1);
    return;
  }
  // ranges::for_each(seq_intervals, [](const auto &si) { println(si.l, si.r, si.belong_to); });

  vector<pair<int, int>> furthest_rights_from(target_len, {-1, -1});
  for (const auto &closure : seq_intervals)
  {
    int cur_l = closure.l;
    if (furthest_rights_from[cur_l].second < closure.r)
    {
      furthest_rights_from[cur_l].first = closure.belong_to;
      furthest_rights_from[cur_l].second = closure.r;
    }
  }
  // cout << furthest_rights_from << "\n";

  vector<pair<int, int>> ans;
  ans.reserve(target_len);
  int l_nxt = 0;
  for (int l = 0; l < target_len; l++)
  {
    int seq_idx = furthest_rights_from[l].first;
    int seq_r   = furthest_rights_from[l].second;
    if (seq_r == -1)
      continue;
    if (!ans.empty())
    {
      int reachable_r = ans.back().second + sza(sub_seqs[ans.back().first]);
      if (seq_r - sza(sub_seqs[seq_idx]) > reachable_r)
      {
        println(-1);
        return;
      }
    }
    if (seq_r == target_len - 1)
    {
      ans.emplace_back(make_pair(seq_idx, l));
      break;
    }

    int optim_l = l;
    int optim_r = seq_r;
    int optim_seq_idx = seq_idx;
    while (l_nxt <= seq_r + 1)
    {
      int nxt_seq_idx = furthest_rights_from[l_nxt].first;
      int nxt_seq_r   = furthest_rights_from[l_nxt].second;
      if (nxt_seq_r <= seq_r)
      {
        l_nxt++;
        continue;
      }

      if (nxt_seq_r > optim_r)
      {
        optim_l = l_nxt;
        optim_r = nxt_seq_r;
        optim_seq_idx = nxt_seq_idx;
      }
      l_nxt++;
    }
    if (optim_r != seq_r && optim_seq_idx != seq_idx)
    {
      ans.emplace_back(make_pair(seq_idx, l));
      ans.emplace_back(make_pair(optim_seq_idx, optim_l));
    }

    l = seq_r + 1;
  }
  ans.shrink_to_fit();

  if (ans.empty())
  {
    println(-1);
    return;
  }
  int reachable_r = ans.back().second + sza(sub_seqs[ans.back().first]);
  if (reachable_r < target_len - 1)
  {
    println(-1);
    return;
  }

  println(sza(ans));
  for (const auto &[seq_idx, l] : ans)
    println(seq_idx + 1, l + 1);
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
