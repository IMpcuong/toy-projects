# Link: https://codeforces.com/contest/1987/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    heights = input_to_list()
    dp = [0]
    for i in range(n - 1, -1, -1):
        if i == n - 1:
            dp[0] = heights[i]
        else:
            if heights[i] > heights[i + 1]:
                block_times = dp[0] - heights[i + 1]
                diff = heights[i] - heights[i + 1]
                if block_times >= diff:
                    dp[0] += 1
                else:
                    dp[0] += diff - block_times  # (heights[i] - blocks) - heights[i + 1]
            else:
                dp[0] += 1
    return dp[0]


for _ in range(input_to_int()):
    print(solve())
