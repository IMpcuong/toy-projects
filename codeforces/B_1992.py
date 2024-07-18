# Link: https://codeforces.com/problemset/problem/1992/B

t = int(input())
for _ in range(t):
    n, k = list(map(int, input().split()))
    arr = list(map(int, input().split()))
    arr.sort()
    moves = 0
    for i in range(k - 1):
        moves += 1 if arr[i] == 1 else (2 * arr[i] - 1)
    print(moves)
