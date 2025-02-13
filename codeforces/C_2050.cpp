#include <bits/stdc++.h>

// clang++ -isystem . -std=c++20 -Wall -Wextra -O2 tmpl.cpp -o out -v

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
void print(const Args &...args) { (std::cout << ... << args); }

template <typename... Args>
void println(const Args &...args) { (std::cout << ... << args) << "\n"; }

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
#define us unsigned short
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

bool solve()
{
  string num_str;
  cin >> num_str;

  // @Note: The semantics of zero-allocation include zero-copying and zero-move.
  //  us known_size = num_str.size();
  //  ar<us, known_size> all_digits;
  vector<us> all_digits;
  all_digits.reserve(num_str.size());
  us counter_twos = 0;
  us counter_threes = 0;
  for (auto &chr : num_str)
  {
    // @Note: Another type conversion tactic:
    //  us digit = static_cast<us>(atoi(chr.c_str()));
    us digit = static_cast<us>(stoi(string(1, chr)));
    if (digit == 2)
      counter_twos += 1;
    else if (digit == 3)
      counter_threes += 1;
    all_digits.emplace_back(digit); // @Note: vector::emplace_back > vector::push_back.
  }

  long cur_sum = accumulate(all_digits.begin(), all_digits.end(), 0);
  if (cur_sum % 9 == 0)
    return true;

  us max_eval_two = counter_twos >= 8 ? 8 : counter_twos;
  us max_eval_three = counter_threes >= 8 ? 8 : counter_threes;

  // @Note:
  //  +> [cur_sum + (2x + 6y)] % 9 >= 0
  //  +> 0 <= x, y <= 8
  us increasable_amount = 0;
  for (us x = 0; x <= max_eval_two; x++)
  {
    for (us y = 0; y <= max_eval_three; y++)
    {
      increasable_amount = 2 * x + 6 * y;
      cur_sum += increasable_amount;
      if (cur_sum % 9 == 0)
        return true;
      else
        cur_sum -= increasable_amount;
    }
  }

  return false;
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
    bool divisible = solve();
    if (divisible)
      println("YES");
    else
      println("NO");
  }
}
