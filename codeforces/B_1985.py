# Link: https://codeforces.com/problemset/problem/1985/B

t = int(input())
for _ in range(t):
    n = int(input())
    arr = [0] * 101
    for x in range(2, n + 1):
        k = n // x
        s = x * (k + 1) * k / 2
        arr[x] = s
    sorted_arr = sorted(arr)
    for i, s in enumerate(arr):
        if s == sorted_arr[-1]:
            print(i)
