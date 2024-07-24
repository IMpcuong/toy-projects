# Link: https://codeforces.com/problemset/problem/1972/A

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    j = 0
    for i in range(n):
        if a[j] <= b[i]:
            j += 1
    print(n - j)
