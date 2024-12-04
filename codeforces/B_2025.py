# Link: https://codeforces.com/contest/1987/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list[int]:
    pairs = input_to_int()
    _ = input_to_list()
    arr_k = input_to_list()
    ans = [0] * pairs
    for i, k in enumerate(arr_k):
        ans[i] = (2**k) % (10**9 + 7)
    return ans


[print(ans) for ans in solve()]
