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
            print(f"1> [{i}]: p: {picked} | w: {win_times}")
            continue
        elif val >= l and val <= r:
            picked += 1
            win_times += 1
            i = picked
            print(f"2> [{i}]: p: {picked} | w: {win_times}")
            continue
        elif val < l:
            picked += 1
            sum = val
            while picked < n:
                sum += cards[picked]
                if sum > r:
                    break
                elif sum < l:
                    picked += 1
                elif l <= sum <= r:
                    win_times += 1
                    picked += 1
                    break
            print(f"3> [{i}]: p: {picked} | s: {sum} | w: {win_times}")
            i = picked
            continue
    return win_times

for _ in range(input_to_int()):
    print(solve())
