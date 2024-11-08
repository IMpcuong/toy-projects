# Link: https://codeforces.com/contest/2033/problem/D

import sys
from typing import Dict, List


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


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
    # print(map_remain_sum)

    s_dp = sum(a[1:])
    dp = [0] * n
    for i in range(n):
        if i == 0:
            if a[i] == 0:
                dp[0] = 1
        else:
            s_dp -= a[i]
            # print(i, s_dp)
            same_sum_indices = map_remain_sum[s_dp]
            # print(same_sum_indices)
            l = len(same_sum_indices)
            tmp_idx = -n
            for j in range(l):
                start_zero_sum_seq = same_sum_indices[j]
                end_zero_sum_seq = i
                mark_start_zero_seq = same_sum_indices[j - 1]
                if end_zero_sum_seq <= start_zero_sum_seq:
                    if j == 0:
                        break
                    tmp_idx = mark_start_zero_seq
                    same_sum_indices = same_sum_indices[j:]
                    map_remain_sum[s_dp] = same_sum_indices
                    break
            # print(tmp_idx)
            dp[i] = dp[i - 1]
            if tmp_idx == -n:
                continue
            dp_tmp = 1
            if tmp_idx == -1:
                if dp_tmp > dp[i]:
                    dp[i] = dp_tmp
                # print("1>>>>>", dp[i])
            else:
                dp_tmp = dp[tmp_idx] + 1
                if dp_tmp > dp[i]:
                    dp[i] = dp_tmp
                # print("2>>>>>", dp[i])
    return dp[-1]


for _ in range(input_to_int()):
    print(solve())
