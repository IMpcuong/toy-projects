# Link: https://codeforces.com/problemset/problem/1945/B

t = int(input())
for _ in range(t):
    a, b, m = list(map(int, input().split()))
    c1 = m // a + 1
    c2 = m // b + 1
    print(c1 + c2)
