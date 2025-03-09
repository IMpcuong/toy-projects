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

pair<int, int> solve()
{
  int k;
  cin >> k;
  vector<int> a(k);
  for (int i = 0; i < k; i++)
    cin >> a[i];

  vector<int> freq(k + 1);
  for (int i = 0; i < k; i++)
    if (freq[a[i]] < 2)
      freq[a[i]]++;
  
  //
  // @Note: k = 2 + n * m.
  //

  pair<int, int> p;
  vector<bool> divisible(k);
  int mult = k - 2;
  for (int i = 0; i < k; i++)
  {
    int divisor = a[i];
    int quotient = mult / divisor;
    if (mult < divisor || mult % divisor != 0)
      continue;

    divisible[divisor] = true;
    if (divisor == quotient)
    {
      if (freq[divisor] == 2)
      {
        p.first = divisor;
        p.second = divisor;
        break;
      }
    }
    else
    {
      if (divisible[quotient])
      {
        p.first = divisor;
        p.second = quotient;
        break;
      }
    }
  }

  return p;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++)
  {
    // cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    auto ans = solve();
    println(ans.first, ans.second);
  }
}
