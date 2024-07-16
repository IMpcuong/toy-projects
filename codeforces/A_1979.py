# Link: https://codeforces.com/problemset/problem/1979/A

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    max_arr = []
    for i in range(n - 1):
        max_arr.append(max(arr[i], arr[i + 1]) - 1)
    print(min(max_arr))
