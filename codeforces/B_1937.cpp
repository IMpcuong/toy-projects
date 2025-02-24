#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -g -Wall -Wextra -O2 tmpl.cpp -o out

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
  ((std::cout << (end ? (end = false, "") : " ") << args), ...);
}

template <typename... Args>
void println(const Args &...args)
{
  bool end = true;
  ((std::cout << (end ? (end = false, "") : " ") << args), ...) << "\n";
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

pair<string, int> solve()
{
  int col;
  string bin_str_f; // f := first
  string bin_str_s; // s := second
  cin >> col;
  cin >> bin_str_f;
  cin >> bin_str_s;

  const int row = 2;
  char bin_mat[row][col];
  strncpy(bin_mat[0], bin_str_f.c_str(), static_cast<size_t>(col));
  strncpy(bin_mat[1], bin_str_s.c_str(), static_cast<size_t>(col));

  string smallest_str = string(1, bin_mat[0][0]);
  int optimal_str_cnt = 1;
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      char right;
      if (j < col - 1)
        right = bin_mat[i][j + 1];
      else
        right = '\0';

      char below;
      if (i < row - 1)
        below = bin_mat[i + 1][j];
      else
        below = '\0';

      if (right > below && below != '\0')
      {
        smallest_str += below;
        i = 1;
        if (j < col - 1)
        {
          smallest_str.append(
              bin_str_s.substr(j + 1,
                               col - j - 2
                               /* Ignores the last char (redundancy from (1)) */));
          break;
        }
      }
      else if (below > right && right != '\0')
      {
        smallest_str += right;
        optimal_str_cnt = 1;
      }
      else if (below == right && below != '\0')
      {
        smallest_str += right;
        optimal_str_cnt += 1;
      }
    }
  }
  smallest_str += string(1, bin_mat[row - 1][col - 1]); // @Note: (1).
  return pair(smallest_str, optimal_str_cnt);
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
    const auto &ans = solve(); // @Note: Another approach is to use std::tuple.
    println(ans.first);
    println(ans.second);
  }
}
