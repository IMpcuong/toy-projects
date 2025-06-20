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

void print_chunks(const vector<chunk_t> &chunks)
{
  for (int i = 0; i < sza(chunks); i++)
  {
    println(chunks[i].type, chunks[i].quan);
    cout << chunks[i].indices << "\n";
  }
}

void solve()
{
  auto n = nxt<int>();
  auto s = nxt<string>();

  vector<chunk_t> chunks;
  chunks.reserve(n);
  // s += 'a' - s[n - 1];
  stack<int> same_type_indices;
  for (int i = 0; i < n; i++)
  {
    if (same_type_indices.empty())
    {
      same_type_indices.push(i);
      continue;
    }

    int top_idx = same_type_indices.top();
    if (s[top_idx] == s[i])
    {
      same_type_indices.push(i);
      continue;
    }

    int chunk_quan = sza(same_type_indices);
    chunk_t chunk = {.type = s[top_idx], .quan = chunk_quan};
    while (!same_type_indices.empty())
    {
      chunk.indices.emplace_back(same_type_indices.top());
      same_type_indices.pop();
    }
    chunks.emplace_back(chunk);

    same_type_indices.push(i);
  }

  int chunk_quan = sza(same_type_indices);
  chunk_t chunk = {.type = s[same_type_indices.top()], .quan = chunk_quan};
  while (!same_type_indices.empty())
  {
    chunk.indices.emplace_back(same_type_indices.top());
    same_type_indices.pop();
  }
  chunks.emplace_back(chunk);
  chunks.shrink_to_fit();

  vector<int> colored_ans(n);
  int merge_or_remove_quan_after_each_epoch = 0;

  int chunk_sz = sza(chunks);
  while (chunk_sz > 0)
  {
    int min_chunk_quan = n;
    for (int i = 0; i < chunk_sz; i++)
      if (chunks[i].quan != 0)
        min_chunk_quan = min(min_chunk_quan, chunks[i].quan);

    for (auto &chunk : chunks)
    {
      if (chunk.quan >= min_chunk_quan)
      {
        for (int j = 0; j < min_chunk_quan; j++)
        {
          int idx = chunk.indices[j];
          colored_ans[idx] = merge_or_remove_quan_after_each_epoch + j + 1;
        }

        chunk.quan -= min_chunk_quan;
        if (chunk.quan == 0)
          chunk.indices.clear();
        else
          chunk.indices.erase(chunk.indices.begin(),
              chunk.indices.begin() + min_chunk_quan);
      }
    }

    int tmp_chunk_sz = sza(chunks);
    vector<chunk_t> epoch_chunks;
    epoch_chunks.reserve(tmp_chunk_sz);
    for (auto &chunk : chunks)
    {
      if (sza(chunk.indices) == 0)
        continue;

      if (epoch_chunks.empty())
      {
        epoch_chunks.emplace_back(chunk);
        continue;
      }

      if (epoch_chunks.back().type != chunk.type)
      {
        epoch_chunks.emplace_back(chunk);
      }
      else
      {
        auto &top_chunk_indices = epoch_chunks.back().indices;
        top_chunk_indices.insert(top_chunk_indices.end(), all(chunk.indices));

        epoch_chunks.back().indices = top_chunk_indices;
        epoch_chunks.back().quan = sza(top_chunk_indices);
      }
    }
    epoch_chunks.shrink_to_fit();

    int new_chunk_sz = sza(epoch_chunks);
    merge_or_remove_quan_after_each_epoch += min_chunk_quan;
    chunks.assign(all(epoch_chunks));
    chunk_sz = new_chunk_sz;
  }

  set<int> seq_cnt = set(all(colored_ans));
  println(sza(seq_cnt));
  cout << colored_ans << "\n";
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
