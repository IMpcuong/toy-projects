# Link: https://codeforces.com/problemset/problem/2009/C

from math import ceil


t = int(input())
while t > 0:
    x, y, k = map(int, input().split())
    # Approach 1:
    x = ceil(x / k)
    y = ceil(y / k)
    if x > y:
        print(2 * x - 1)
    else:
        print(2 * y)

    # Approach 2: TLE
    # s = [0, 0]
    # turn = 0
    # steps = 0
    # while s[0] < x or s[1] < y:
    #     s[turn] += k
    #     turn = 1 - turn
    #     steps += 1
    # print(steps)
    t -= 1