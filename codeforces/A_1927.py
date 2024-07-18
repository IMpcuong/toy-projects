# Link: https://codeforces.com/problemset/problem/1927/A

t = int(input())
for _ in range(t):
    n = int(input())
    strip = input()
    blacks = []
    for i in range(n):
        if strip[i] == "B":
            blacks.append(i)
    if len(blacks) == 1:
        print(1)
    else:
        print(blacks[-1] - blacks[0] + 1)
