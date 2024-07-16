# Link: https://codeforces.com/problemset/problem/1929/A

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()
    s = [arr[i + 1] - arr[i] for i in range(n - 1)]
    print(sum(s))
