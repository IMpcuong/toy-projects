# Link: https://codeforces.com/problemset/problem/1989/A

t = int(input())
while t > 0:
    x, y = map(int, input().split())
    print("YES" if y >= -1 else "NO")
    t -= 1
