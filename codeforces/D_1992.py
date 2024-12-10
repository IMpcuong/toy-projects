# Link: https://codeforces.com/problemset/problem/1992/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())

_y = "YES"
_n = "NO"


def solve() -> bool:
    n, jump_dist, total_swim_dist = input_to_map()
    route = input()
    route = "L" + route + "L"  # NOTE: Treating shore/bank == log (equivalent/).
    n += 2
    log_indices = []
    for i in range(n):
        obj = route[i]
        if obj == "L":
            log_indices.append(i)
    num_log = len(log_indices)
    # NOTE:
    passed_water = 0
    for i in range(num_log - 1):
        cur_log = log_indices[i]
        next_log = log_indices[i + 1]
        pos_after_jump = cur_log + jump_dist
        # NOTE: O(n):
        #   + log_indices := [l_i | i := {0, k}; l_k = n - 1 && l_0 = 0] (1).
        #   + Each loop := l_i -> l_{i + 1} -> time complexity := l_{i + 1} - l_i (2).
        #   (1) + (2) -> time complexity := (l_1 - l_0) + (l_2 - l_1) + ... + (l_k - l_{k - 1})
        #                                := l_k - l_0 := (n - 1) - 0 = n - 1 = len(route).
        for j in range(cur_log + 1, next_log):
            if route[j] == "C" and pos_after_jump <= j:
                return False
        remain_water_per_segment = 0
        if pos_after_jump < next_log:
            remain_water_per_segment = next_log - pos_after_jump
        passed_water += remain_water_per_segment
        if passed_water > total_swim_dist:
            return False
    return True


for _ in range(input_to_int()):
    print(_y if solve() else _n)
