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

const string DESIRED_STR = "narek";
const int DESIRED_STR_LEN = sza(DESIRED_STR);

int solve()
{
  int quantity, sample_len;
  cin >> quantity >> sample_len;

  vector<string> samples(quantity);
  for (int i = 0; i < quantity; i++)
    cin >> samples[i];

  const auto NEGATIVE_INF = static_cast<int>(-INF);
  vector<int> dp(DESIRED_STR_LEN, NEGATIVE_INF);
  dp[0] = 0;
  vector<int> tmp_dp;
  for (int i = 0; i < quantity; i++)
  {
    tmp_dp = dp;
    for (int j = 0; j < DESIRED_STR_LEN; j++)
    {
      if (dp[j] == NEGATIVE_INF)
        continue;

      int bonus_score = 0;
      int next_desired_chr_idx = j;
      for (int k = 0; k < sample_len; k++)
      {
        char cur_chr = samples[i][k];
        int chr_idx = DESIRED_STR.find(cur_chr);
        if (chr_idx == -1)
          continue;

        if (chr_idx == next_desired_chr_idx)
        {
          next_desired_chr_idx = (next_desired_chr_idx + 1) % DESIRED_STR_LEN;
          bonus_score++; // @Note: human_bonus_score += 1.
        }
        else
        {
          bonus_score--; // @Note: bot_bonus_score += 1.
        }
      }
      tmp_dp[next_desired_chr_idx] = max(tmp_dp[next_desired_chr_idx], dp[j] + bonus_score);
    }
    dp = tmp_dp;
  }

  int ans = 0;
  for (int i = 0; i < DESIRED_STR_LEN; i++)
    ans = max(ans, dp[i] - 2 * i);

  return ans;
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
    println(solve());
  }
}
