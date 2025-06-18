#include <algorithm>
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

struct chunk_t
{
  char type;
  int quan;
  vector<int> indices;
};

void solve()
{
  auto n = nxt<int>();
  auto s = nxt<string>();

  vector<chunk_t> chunks;
  chunks.reserve(n);
  int start = 0;
  int end   = 0;
  for (int i = 1; i < n; i++)
  {
    char cur  = s[i];
    char prev = s[i - 1];

    if (prev == cur)
    {
      end = i;
      continue;
    }

    if (start <= end)
    {
      int quan = end - start + 1;
      vector<int> chunk_indices(quan);
      iota(all(chunk_indices), start);
      chunks.emplace_back(chunk_t{s[start], quan, chunk_indices});
    }
    start = i;
    end   = i;
  }
  if (start <= end)
  {
    int quan = end - start + 1;
    vector<int> chunk_indices(quan);
    iota(all(chunk_indices), start);
    chunks.emplace_back(chunk_t{s[start], quan, chunk_indices});
  }
  chunks.shrink_to_fit();

  // for (int i = 0; i < sza(chunks); i++)
  // {
  //   println(chunks[i].type, chunks[i].quan);
  //   cout << chunks[i].indices << "\n";
  // }

  vector<vector<int>> seqs_indices;
  seqs_indices.reserve(n);

  int chunk_sz = sza(chunks);
  while (chunk_sz)
  {
    vector<int> cur_seq_indices;
    int fusion_quan = 0;

    int min_chunk_quan = n;
    for (int i = 0; i < chunk_sz; i++)
      if (chunks[i].quan != 0)
        min_chunk_quan = min(min_chunk_quan, chunks[i].quan);

    for (int i = 0; i < chunk_sz; i++)
    {
      if (chunks[i].quan >= min_chunk_quan)
      {
        chunks[i].quan -= min_chunk_quan;
        cur_seq_indices.insert(cur_seq_indices.end(),
            chunks[i].indices.begin(),
            chunks[i].indices.begin() + min_chunk_quan);
      }
    }
    seqs_indices.emplace_back(cur_seq_indices);

    stack<chunk_t> merged_chunks;
    for (int i = 0; i < chunk_sz; i++)
    {
      if (chunks[i].quan == 0)
      {
        fusion_quan++;
        continue;
      }

      if (merged_chunks.empty())
      {
        merged_chunks.push(chunks[i]);
      }
      else
      {
        auto chunk_tail = merged_chunks.top();
        merged_chunks.pop();
        if (chunk_tail.type == chunks[i].type)
        {
          chunk_tail.indices.insert(chunk_tail.indices.end(), all(chunks[i].indices));
          merged_chunks.push(chunk_tail);
          fusion_quan++;
          continue;
        }

        merged_chunks.push(chunks[i]);
      }
    }

    chunks = {};
    chunks.reserve(sza(merged_chunks));
    while (!merged_chunks.empty())
    {
      chunks.emplace_back(merged_chunks.top());
      merged_chunks.pop();
    }

    chunk_sz -= fusion_quan;
  }
  seqs_indices.shrink_to_fit();

  cout << seqs_indices << "\n";
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
    cout << "Case #" << t << ": "; // @Warn: Commenting before submission.
    solve();
  }
}
