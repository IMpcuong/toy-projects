# Link: https://codeforces.com/problemset/problem/2025/B

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list[int]:
    pairs = input_to_int()
    _ = input_to_list()
    arr_k = input_to_list()
    _mod_val = 10**9 + 7
    max_k = max(arr_k)
    tmp_arr = [1] * (max_k + 1)
    for k in range(1, max_k + 1):
        if k == 1:
            tmp_arr[k] = 2  # n = 2 && k = 1
        else:
            tmp_arr[k] = (2 * tmp_arr[k - 1]) % _mod_val  # 2^k = 2 * 2^(k - 1)
    ans = [0] * pairs
    for i, k in enumerate(arr_k):
        ans[i] = tmp_arr[k]
    return ans


[print(ans) for ans in solve()]
