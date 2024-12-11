# Link: https://codeforces.com/problemset/problem/1982/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n, l, r = input_to_map()
    cards = input_to_list()
    win_times = 0
    picked = 0
    for i in range(n):
        val = cards[i]
        if picked > n:
            break
        if val > r:
            picked += 1
            i = picked
            # print(f"[{i}] {val}> p: {picked} | w: {win_times}")
            continue
        elif val >= l and val <= r:
            picked += 1
            win_times += 1
            i = picked
            # print(f"[{i}] {val}> p: {picked} | w: {win_times}")
            continue
        elif val < l:
            picked += 1
            if i < n - 1 and val + cards[i + 1] > r:
                i = picked
                continue
            sum = val
            while picked < n:
                if sum + cards[picked] <= r:
                    sum += cards[picked]
                    picked += 1
                else:
                    break
            # print(f"[{i}] {val}> p: {picked} | w: {win_times}")
            win_times += 1
            i = picked
            # print(f"[{i}] {val}> p: {picked} | w: {win_times}")
            continue
    return win_times

for _ in range(input_to_int()):
    print(solve())
