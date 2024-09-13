# Link: https://codeforces.com/problemset/problem/1896/A

t = int(input())
for _ in range(t):
    _ = int(input())
    a = list(map(int, input().split()))
    print("YES" if a[0] == 1 else "NO")
