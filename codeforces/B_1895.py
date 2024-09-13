# Link: https://codeforces.com/problemset/problem/1895/B

t = int(input())
for _ in range(t):
    p = int(input())  # NOTE: 2 * p = len(a)
    a = list(map(int, input().split()))
    a.sort()
    min_d = (a[p - 1] - a[0]) + (a[2 * p - 1] - a[p])
    print(min_d)
    [print(a[i], a[i + p]) for i in range(p)]
