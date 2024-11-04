# Link: https://codeforces.com/contest/2033/problem/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    a = input_to_list()
    dp = [0] * n
    for i in range(n):
        if i == 0:
            if a[i] == 0:
                dp[0] = 1
        else:
            s = sum(a[0 : i + 1])
            segments = 0
            if s == 0:
                segments += 1
            for j in range(i):
                s -= a[j]  # s = sum(a[j + 1 : i + 1])
                # print(f">>>>> i ~ {i} | j ~ {j} | s ~ {s}")
                if s == 0:
                    if segments < dp[j] + 1:
                        segments = dp[j] + 1
            if dp[i - 1] < segments:
                dp[i] = segments
            else:
                dp[i] = dp[i - 1]
    return dp[-1]


for _ in range(input_to_int()):
    print(solve())
