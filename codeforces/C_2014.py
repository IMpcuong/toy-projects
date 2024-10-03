# Link: https://codeforces.com/problemset/problem/2014/C

import sys
from math import gcd


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    a = input_to_list()

    # Approach 1:
    a.sort()
    if n == 1 or n == 2:
        return -1
    mid = n // 2
    if sum(a) / n > 2 * a[mid]:
        return 0
    x = 2 * n * a[mid] - sum(a) + 1
    return x


for _ in range(input_to_int()):
    print(solve())
