# Link: https://codeforces.com/problemset/problem/1941/B

t = int(input())
while t > 0:
    n = int(input())
    a = list(map(int, input().split()))
    violated = False
    for i in range(n - 2):  # NOTE: a[n - 3] | a[n - 2] | a[n - 1]
        v = a[i]
        if v < 0:
            violated = True
            break
        a[i] -= v
        a[i + 1] -= 2 * v
        a[i + 2] -= v
    if not violated and a[-2] == a[-1] == 0:
        print("YES")
    else:
        print("NO")
    t -= 1
