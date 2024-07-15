# Link: https://codeforces.com/problemset/problem/1984/A

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    if arr[0] == arr[-1]:
        print("NO")
    else:
        print("YES")
        valid_str = "RB" + "R" * (n - 2)
        print(valid_str)
