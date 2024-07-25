# Link: https://codeforces.com/problemset/problem/1930/B

# T = int(input())
# while T > 0:
#     n = int(input())
#     a = [0] * n
#     for i in range(n + 1 >> 1):
#         a[i << 1] = i + 1
#     for i in range(n >> 1):
#         a[i << 1 | 1] = n - i
#     print(*a)
#     T -= 1

t = int(input())
for _ in range(t):
    l = int(input())
    for i in range(1, l // 2 + 1):
        print(i, l + 1 - i, end=" ")
    if l & 1:
        print(l // 2 + 1, end="")
    print("")
