# Link: https://codeforces.com/problemset/problem/1992/A

t = int(input())
max_turn = 5
for _ in range(t):
    arr = list(map(int, input().split()))
    for i in range(max_turn):
        arr.sort()
        arr[0] += 1
    print(arr[0] * arr[1] * arr[2])
