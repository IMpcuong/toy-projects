# Link: https://codeforces.com/problemset/problem/1982/A

t = int(input())
for _ in range(t):
    x1, x2 = list(map(int, input().split()))
    y1, y2 = list(map(int, input().split()))
    print("NO" if (x1 < x2) and (y1 > y2) or (x1 > x2) and (y1 < y2) else "YES")
