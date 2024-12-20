# Link: https://codeforces.com/problemset/problem/1686/B

import sys
from typing import Dict, List


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    permutation = input_to_list()
    list_indices_asc_by_value = sorted(range(n), key=lambda i: -permutation[i])
    _invalid_val = -1
    counter = 0
    for idx in list_indices_asc_by_value:
        if idx == n - 1:
            continue
        cur_val = permutation[idx]
        next_val = permutation[idx + 1]
        if cur_val > next_val and next_val != _invalid_val:
            counter += 1
            permutation[idx] = _invalid_val
            permutation[idx + 1] = _invalid_val
    return counter


for _ in range(input_to_int()):
    print(solve())
