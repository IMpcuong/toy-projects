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
        if picked > n:
            break
        if i < picked:
            continue
        val = cards[i]
        if val > r:
            picked += 1
        elif val >= l and val <= r:
            picked += 1
            win_times += 1
            # print(f"0 [{i}]> p: {picked} | w: {win_times}")
        elif val < l:
            picked += 1
            firstPicked = picked
            lastPicked = picked
            while firstPicked <= lastPicked and lastPicked < n:
                val += cards[lastPicked]
                lastPicked += 1
                # print(f"1 [{i}]> f: {firstPicked} | l: {lastPicked} | v: {val} | w: {win_times}")
                if l <= val <= r:
                    picked = lastPicked
                    win_times += 1
                    # print(f"2 [{i}]> f: {firstPicked} | l: {lastPicked} | v: {val} | w: {win_times}")
                    break
                while val > r and firstPicked <= lastPicked:
                    val -= cards[firstPicked - 1]
                    firstPicked += 1
                    if l <= val <= r:
                        firstPicked = lastPicked + 1
                        win_times += 1
                        # print(f"3.1 [{i}]> f: {firstPicked} | l: {lastPicked} | v: {val} | w: {win_times}")
                        break
                    elif val < l:
                        # print(f"3.2 [{i}]> f: {firstPicked} | l: {lastPicked} | v: {val} | w: {win_times}")
                        break
                picked = lastPicked
            # print(f"3> p: {picked} | s: {val} | w: {win_times}")
    return win_times


for _ in range(input_to_int()):
    print(solve())
