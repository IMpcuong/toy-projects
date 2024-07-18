# Link: https://codeforces.com/problemset/problem/1930/A

t = int(input())
for _ in range(t):
    n = int(input())
    arr_2n = list(map(int, input().split()))
    arr_2n.sort(reverse=True)
    score, k = 0, 0
    for _ in range(n):
        score += min(arr_2n[k], arr_2n[k + 1])
        k += 2
    print(score)
