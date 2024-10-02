# Link: https://codeforces.com/problemset/problem/2004/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n, k = input_to_map()
    a = input_to_list()
    a.sort(reverse=True)
    first = []
    second = []
    i = 0
    while i < n:
        first.append(a[i])
        if i == n - 1:
            break
        d = a[i] - a[i + 1]
        if d <= k:
            a[i + 1] += d
            k -= d
        else:
            a[i + 1] += k
            k = 0
        second.append(a[i + 1])
        i += 2
    return sum(first) - sum(second)


for _ in range(input_to_int()):
    print(solve())
