# Link: https://codeforces.com/problemset/problem/1809/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list:
    n, k = input_to_map()
    res = [-2] * n
    i = 0
    while k > 0:
        res[i] = 2 * k - 1
        if k > n:
            k -= n
            n -= 1
        else:
            k = 0
        i += 1
    return res


for _ in range(input_to_int()):
    print(*solve())
