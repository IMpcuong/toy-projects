# Link: https://codeforces.com/contest/2033/problem/D

import sys
from typing import Dict, List


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def binary_search_closest_upper(
    cur_idx: int, indices: List[int], len_indices: int
) -> int:
    closest_upper_idx_in_indices = 0
    prev_same_sum_idx = -len_indices
    l, r = 0, len_indices
    while l <= r:
        mid_idx = (l + r) // 2
        v = indices[mid_idx]
        if cur_idx > v:
            l = mid_idx
        elif cur_idx < v:
            r = mid_idx
        else:
            closest_upper_idx_in_indices = mid_idx
            break
    if closest_upper_idx_in_indices == 0:
        return prev_same_sum_idx
    prev_same_sum_idx = indices[closest_upper_idx_in_indices - 1]
    return prev_same_sum_idx


def solve() -> int:
    n = input_to_int()
    a = input_to_list()

    map_remain_sum: Dict[int, List[int]] = {sum(a): [-1]}
    s = sum(a[1:])
    for i in range(n):
        if i != 0:
            s -= a[i]
        if s not in map_remain_sum:
            map_remain_sum[s] = []
        map_remain_sum[s].append(i)
    for indices in map_remain_sum.values():
        indices.sort()

    s_dp = sum(a[1:])
    dp = [0] * n
    for i in range(n):
        if i == 0:
            if a[i] == 0:
                dp[0] = 1
        else:
            s_dp -= a[i]
            same_sum_indices = map_remain_sum[s_dp]
            l = len(same_sum_indices)
            tmp_idx = binary_search_closest_upper(i, same_sum_indices, l)
            dp[i] = dp[i - 1]
            if tmp_idx == -l:
                continue
            dp_tmp = 1
            if tmp_idx == -1:
                if dp_tmp > dp[i]:
                    dp[i] = dp_tmp
            else:
                dp_tmp = dp[tmp_idx] + 1
                if dp_tmp > dp[i]:
                    dp[i] = dp_tmp
    return dp[-1]


for _ in range(input_to_int()):
    print(solve())
