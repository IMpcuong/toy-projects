# Link: https://codeforces.com/problemset/problem/2007/C

import sys
from math import gcd


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    # NOTE: x' = x + (a * i + b * j) -> x = x' + k * gcd(a, b).
    n, a, b = input_to_map()
    # NOTE:
    # + upper = l * gcd(a, b) | l := [1, inf]
    #   -> lim(c[i] // gcd(a, b)) = upper | i := [0, n - 1].
    # + c[i] = (c[i] // gcd(a, b)) * gcd(a, b) + c[i] % gcd(a, b).
    #   -> c[i] - c[i] % gcd(a, b) = (c[i] // gcd(a, b)) * gcd(a, b).
    #   -> c[i] - c[i] % gcd(a, b) = k * gcd(a, b) | k = const.
    c = input_to_list()
    chunk = gcd(a, b)
    remains = [c[i] % chunk for i in range(n)]
    sorted_remains = sorted(set(remains))
    ma, mi = max(sorted_remains), min(sorted_remains)
    delta = ma - mi
    for i in range(len(sorted_remains) - 1):
        sorted_remains[i] += chunk
        # NOTE:
        # + sorted_remains[i] < sorted_remains[i + 1] | i := [0, len(sorted_remains) - 2].
        # + sorted_remains[i] = c[i] % gcd(a, b) < gcd(a, b) | i := [0, len(sorted_remains) - 1].
        #   -> sorted_remains[i] + gcd(a, b) = max(sorted_remains) | i := [0, len(sorted_remains) - 1].
        #   -> sorted_remains[i + 1] < sorted_remains[i + 2]
        #      < gcd(a, b) < gcd(a, b) + sorted_remains[i] | i := [0, len(sorted_remains) - 3].
        #   -> sorted_remains[i + 1] = min(sorted_remains) | i := [0, len(sorted_remains) - 2].
        delta_t = sorted_remains[i] - sorted_remains[i + 1]
        if delta_t < delta:
            delta = delta_t
    return delta


for _ in range(input_to_int()):
    print(solve())