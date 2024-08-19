# Link: https://codeforces.com/problemset/problem/1921/C

t = int(input())
while t > 0:
    n, f, a, b = list(map(int, input().split()))
    m = [0] + list(map(int, input().split()))
    # consumed = max(f - m[-1] * a, f - n * b)
    for i in range(1, n + 1):
        f -= min(a * (m[i] - m[i - 1]), b)
    print("YES" if f > 0 else "NO")
    t -= 1
