# Link: https://codeforces.com/problemset/problem/1881/A

t = int(input())
while t > 0:
    l_x, l_s = map(int, input().split())
    x, s = input(), input()
    ops = 0
    while s not in x:
        if l_x > l_s:
            x += x
            ops += 1
            break
        x += x
        l_x <<= 1  # l_x = l_x * 2
        ops += 1
    print(ops if s in x else -1)
    t -= 1
