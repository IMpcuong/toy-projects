# Link: https://codeforces.com/problemset/problem/1933/A

t = int(input())
while t > 0:
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    a = [-a[i] if a[i] < 0 else a[i] for i in range(n)]
    print(sum(a))
    t -= 1