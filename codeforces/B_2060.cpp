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
  string sep;
  for (const T &x : v)
    os << sep << x, sep = " ";
  return os;
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
  auto m = nxt<int>();
  vector<vector<int>> hands(n);
  for (int i = 0; i < n; i++)
  {
    vector<int> cards(m);
    generate(all(cards), nxt<int>);
    sort(all(cards), greater<int>());
    hands[i] = cards;
  }

  vector<int> permut;
  permut.reserve(n);
  bool winnable = true;

  vector<pair<int, int>> turn_order(n);
  for (int i = 0; i < n; i++)
  {
    int throwed = hands[i].back();
    turn_order[i] = pair(i, throwed);
  }
  auto cmp = [](const auto &p1, const auto &p2) -> bool
  {
    return p1.second < p2.second;
  };
  sort(all(turn_order), cmp);
  // @Note: The first phase has always been playable.
  for_each(all(turn_order), [&](const auto &p) { permut.emplace_back(p.first); });

  // cout << permut << "\n";

  int biggest_card = -1;
  while (m && n != 1)
  {
    for (const auto &turn : permut)
    {
      int throwed_by_order = hands[turn].back();
      hands[turn].pop_back();
      if (throwed_by_order > biggest_card)
      {
        biggest_card = throwed_by_order;
        continue;
      }

      winnable = false;
      goto OUTER;
    }
    m--;
  }

OUTER:
  if (!winnable)
  {
    permut.clear();
    permut.emplace_back(-1);
  }
  else
  {
    for_each(all(permut), [&](auto &turn) { turn++; });
  }

  cout << permut << "\n";
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
