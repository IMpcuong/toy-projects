# Link: https://codeforces.com/problemset/problem/2019/B

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
    freq = {k: 0 for k in queries}
    # NOTE:
    #   + nCk | k = 2 := n! / (2! * (n - 2)!) = (n * (n - 1)) / 2.
    calc_comb_fn_once = lambda x: (x * (x - 1)) // 2
    total_combs = calc_comb_fn_once(n)
    for i in range(n - 1):
        l, r = i, i + 1
        l_combs, r_combs = 0, 0
        occurs = 0
        if r == 1:
            r_points = n - r
            r_combs = calc_comb_fn_once(r_points)
        elif r == n - 1:
            l_points = r
            l_combs = calc_comb_fn_once(l_points)
        else:
            l_points, r_points = r, n - r
            l_combs, r_combs = calc_comb_fn_once(l_points), calc_comb_fn_once(r_points)
        occurs = total_combs - (l_combs + r_combs)
        num_ele = segments[r] - segments[l] - 1
        if occurs not in freq:
            freq[occurs] = num_ele
        else:
            freq[occurs] += num_ele
    for i in range(n):
        r = n - i
        l = i
        occurs = (l * r) + r - 1
        if occurs not in freq:
            freq[occurs] = 1
        else:
            freq[occurs] += 1
    for i in range(q):
        queries[i] = freq[queries[i]]
    return queries


for _ in range(input_to_int()):
    print(*solve())
