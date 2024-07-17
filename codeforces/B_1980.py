# Link: https://codeforces.com/problemset/problem/1980/B

t = int(input())
for _ in range(t):
    n, f, k = list(map(int, input().split()))
    arr = list(map(int, input().split()))
    pivot = arr[f - 1]
    arr.sort(reverse=True)
    freq_pivot_full = arr.count(pivot)
    freq_pivot_cutset = arr[:k].count(pivot)
    if freq_pivot_cutset == 0:
        print("NO")
    elif freq_pivot_cutset == freq_pivot_full:
        print("YES")
    else:
        print("MAYBE")
