# Link: https://codeforces.com/problemset/problem/1987/A

n = int(input())
for _ in range(n):
    ram, time_window = list(map(int, input().split()))
    time_consumed = (ram - 1) * time_window + 1
    print(time_consumed)
