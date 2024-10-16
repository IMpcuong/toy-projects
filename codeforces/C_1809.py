# Link: https://codeforces.com/problemset/problem/1809/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list:
    n, k = input_to_map()
    res = [-2] * n
    # NOTE:
    # + [1, -1, -1] -> k = 1 satisfied the first condition.
    #   However, the condition that all subsequences have a summary that is strictly different from zero
    #   prevents us from using [-1] * n as the base answer.
    # + [1, -2, -2] -> k = 1 satisfied.
    # + [3, -2, -2] -> k = 2 satisfied.
    # + [5, -2, -2] -> k = 3 satisfied.
    #   -> We use -2 as the basis element to apply the "odd-even" rule.
    #   -> res[i] = 2 * k - 1.
    # + [5, 1, -2] -> k = 4 satisfied && k > n.
    #   -> The first element now point the next index by shifting the array by 1 unit.
    #   -> n -= 1.
    #   -> res[i] = 2 * k - 1.
    i = 0
    while k > 0:
        res[i] = 2 * k - 1
        if k > n:
            k -= n
            n -= 1
        else:
            k = 0
        i += 1
    return res


for _ in range(input_to_int()):
    print(*solve())
