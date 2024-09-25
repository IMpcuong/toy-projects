# Link: https://codeforces.com/contest/2013/problem/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def indicate_last_max_idx(n: int, a: list[int]) -> int:
    interm_a = [
        i for i, _ in sorted(enumerate(a), key=lambda x: x[1], reverse=True)
    ]
    for idx in interm_a:
        if idx == n - 1:
            continue
        if a[idx] > a[idx + 1]:
            return idx
    return n - 1


def calc_delta(greater: int, smaller: int) -> int:
    d = greater - smaller
    if d % 2 == 0:
        return d // 2
    return d // 2 + 1


def solve() -> int:
    n = input_to_int()
    a = input_to_list()
    if n == 1:
        return 0
    if n == 2:
        if a[0] == a[1]:
            return 0
        elif a[0] < a[1]:
            return a[1] - a[0]
        return (a[0] - a[1]) % 2
    m_idx = indicate_last_max_idx(n, a)
    while m_idx < n - 1:
        if a[m_idx] < a[m_idx + 1]:
            break
        d = calc_delta(a[m_idx], a[m_idx + 1])
        a[m_idx] -= d
        a[m_idx + 1] += d
        m_idx = indicate_last_max_idx(n, a)
    return max(a) - min(a)


for _ in range(input_to_int()):
    print(solve())