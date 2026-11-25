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

const char _O = '(';
const char _C = ')';

void solve()
{
  auto str_len = nxt<int>();
  auto op = nxt<int>();
  auto bracket_str = nxt<string>();
  assert(str_len == sza(bracket_str));

  deque<pair<char, int>> dq;
  vector<pair<int, int>> valid_seq_ranges;
  valid_seq_ranges.reserve(str_len / 2 + 1);
  int open_cnt = 0;
  for (int i = 0; i < str_len; i++)
  {
    auto cur = bracket_str[i];
    if (dq.empty() && cur == _O)
    {
      open_cnt++;
      dq.push_back(pair{cur, i});
      continue;
    }

    if (!dq.empty())
    {
      if (cur == _C)
      {
        if (open_cnt == 0)
          continue;

        int l = dq.back().second;
        int r = i;
        valid_seq_ranges.emplace_back(pair{l, r});
        dq.pop_back();
        open_cnt--;
      }
      else if (cur == _O)
      {
        open_cnt++;
        dq.push_back(pair{cur, i});
      }
    }
  }
  valid_seq_ranges.shrink_to_fit();
  ranges::sort(valid_seq_ranges, [](const auto &fp, const auto &sp) { return fp.first < sp.first; });

  ranges::fill_n(bracket_str.begin(), str_len, '0');
  if (valid_seq_ranges.empty())
  {
    println(bracket_str);
    return;
  }

  auto pinned_seq = valid_seq_ranges.front();
  vector<pair<int, int>> compacted_valid_seq_ranges = {pinned_seq};
  compacted_valid_seq_ranges.reserve(sza(valid_seq_ranges));
  for (const auto &seq : valid_seq_ranges | ranges::views::drop(1))
  {
    if (pinned_seq.first < seq.first && pinned_seq.second > seq.second)
      continue;

    compacted_valid_seq_ranges.emplace_back(seq);
    pinned_seq = seq;
  }
  ranges::sort(compacted_valid_seq_ranges,
      [](const auto &fp, const auto &sp)
      {
        auto f_len = fp.second - fp.first;
        auto s_len = sp.second - sp.first;
        return f_len > s_len;
      }
  );
  for (const auto &seq : compacted_valid_seq_ranges)
  {
    if (op == 0)
      break;

    auto seq_len = seq.second - seq.first;
    if (op >= seq_len)
    {
      ranges::fill_n(bracket_str.begin() + seq.first, seq_len, '1');
      op -= seq_len;
    }
    else
    {
      ranges::fill_n(bracket_str.begin() + seq.first, op, '1');
      op = 0;
    }
  }

  // println(compacted_valid_seq_ranges);
  println(bracket_str);
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
