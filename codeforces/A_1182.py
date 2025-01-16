# Link: https://codeforces.com/problemset/problem/1182/A

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    if n % 2 != 0:
        return 0
    return 2 ** (n // 2)


print(solve())
