# Link: https://codeforces.com/problemset/problem/1999/E

import sys
from math import floor, log


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def exact_log(num: int, base: int) -> float:
    res = log(num, base)
    rounded = round(res)
    if abs(res - rounded) <= 8.881784197001252e-16:
        return rounded
    return res


def solve() -> int:
    l, r = input_to_map()
    ops = 0
    _base = 3
    for num in range(l, r + 1):
        raw_steps = exact_log(num, _base)
        steps = floor(raw_steps)
        if num == l:
              ops += steps * 2 + 2
        else:
            ops += steps + 1
    return ops


for _ in range(input_to_int()):
    print(solve())
