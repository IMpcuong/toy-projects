# Link: https://codeforces.com/problemset/problem/2014/D

import sys
from math import factorial


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list:
    n, q = input_to_map()
    segments = input_to_list()
    queries = input_to_list()
    q_dict = {k: 0 for k in queries}
    # ???
    if n == 2:
        return []
    f_n = factorial(n)
    f_n_2 = factorial(n - 2)
    total_comb = f_n / (2 * f_n_2)
    # NOTE: f_2 := factorial(2) = 2.
    for chunk in range(n - 1):
        l, r = chunk, chunk + 1
        l_existed, r_existed = 0, 0
        if l == 0:
            f_remain = factorial(n - r)
            f_remain_2 = factorial(n - r - 2)
            r_existed = f_remain / (2 * f_remain_2)
        else:
            f_r = factorial(r)
            f_r_2 = factorial(r - 2)
            if r == n - 1:
                l_existed = f_r / (2 * f_r_2)
            else:
                f_remain = factorial(n - r)
                f_remain_2 = factorial(n - r - 2)
                l_existed = f_r / (2 * f_r_2)
                r_existed = f_remain / (2 * f_remain_2)
        k = total_comb - (l_existed + r_existed)
        q_dict[k] += segments[r] - segments[l]
    return list(q_dict.values())


for _ in range(input_to_int()):
    print(*solve())
