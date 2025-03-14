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
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

constexpr string _Y = "YES";
constexpr string _N = "NO";

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
  vector<long> a(n);
  generate(all(a), nxt<long>);

  auto m = nxt<int>();
  vector<vector<int>> s(m);
  generate(all(s), []() -> vector<int>
                   { 
                     auto s = nxt<string>();
                     auto conv = [&]() -> vector<int>
                     {
                       vector<int> ans(sza(s));
                       for (int i = 0; i < sza(s); i++)
                         ans[i] = static_cast<int>(s[i]);
                       return ans;
                     }();
                     return conv;
                   });
  
  auto match_pattern = [&](const vector<int> &vec) -> bool
  {
    if (sza(vec) != n)
      return false;

    unordered_map<int, int> match_map(n);
    for (int i = 0; i < n; i++)
    {
      if (match_map.find(a[i]) != match_map.end())
      {
        if (match_map[a[i]] != vec[i])
          return false;
        continue;
      }
      match_map[a[i]] = vec[i];
    }

    if (sza(match_map) != sza(set(all(vec))))
      return false;

    return true;
  };

  vector<string> ans;
  ans.reserve(m);
  for (const auto &v : s)
  {
    if (match_pattern(v))
      ans.emplace_back(_Y);
    else
      ans.emplace_back(_N);
  }
  
  for_each(all(ans), println<string>);
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
