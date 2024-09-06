# Link: https://codeforces.com/problemset/problem/1873/D

t = int(input())
while t > 0:
    n, k = map(int, input().split())
    s = input()
    j, ops = 0, 0
    # if "B" in s:
    #     ops += 1
    #     j = s.index("B")
    for i in range(n):
        if s[i] == "B":
            ops += 1
            j = i
            break
    for i in range(j, n):
        if s[i] == "B" and i >= j + k:
            ops += 1
            j = i
    print(ops)
    t -= 1
