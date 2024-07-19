# Link: https://codeforces.com/problemset/problem/1978/B

t = int(input())
for _ in range(t):
    n, a, b = list(map(int, input().split()))
    k_0 = min(n, b)
    k = 0 if (b - a + 1) < 0 else (b - a + 1)
    k = min(k, k_0)
    profit_with_modified_price = (b + (b - k + 1)) * k // 2
    profit_with_usual_price = a * (n - k)
    print(profit_with_modified_price + profit_with_usual_price)
