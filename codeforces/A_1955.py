# Link: https://codeforces.com/problemset/problem/1955/A

t = int(input())
while t > 0:
    n, a, b = list(map(int, input().split()))
    if 2 * a < b:
        print(n * a)
    else:
        print(n // 2 * b if n % 2 == 0 else (n - 1) // 2 * b + a)
    t -= 1
