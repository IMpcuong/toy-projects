# Link: https://codeforces.com/problemset/problem/1999/E

import sys
from math import floor, log


_upper_bound = 2 * 10**5
_base = 3


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


def compute_log_values_from(num_range: int, log_base: int) -> list[int]:
    log_values = []
    for num in range(1, num_range + 1):
        v = floor(exact_log(num, log_base))
        log_values.append(v + 1)
    return log_values


def compute_list_sum_of_log_from(log_values: list[int]) -> list[int]:
    list_sum_of_log = []
    sum_val = 0
    for log_val in log_values:
        sum_val += log_val
        list_sum_of_log.append(sum_val)
    return list_sum_of_log


_precomputed_log_values = compute_log_values_from(
    num_range=_upper_bound, log_base=_base
)
_precomputed_list_sum_of_log = compute_list_sum_of_log_from(_precomputed_log_values)


def solve() -> int:
    l, r = input_to_map()
    smaller_sum = _precomputed_list_sum_of_log[l - 1]
    greater_sum = _precomputed_list_sum_of_log[r - 1]
    ops = (greater_sum - smaller_sum) + _precomputed_log_values[l - 1] * 2
    return ops


for _ in range(input_to_int()):
    print(solve())
