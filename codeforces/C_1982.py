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
            # print(f"1> p: {picked} | w: {win_times}")
        elif val >= l and val <= r:
            picked += 1
            win_times += 1
            # print(f"2> p: {picked} | w: {win_times}")
        elif val < l:
            picked += 1
            while picked < n:
                val += cards[picked]
                firstPicked = picked - 1
                lastPicked = picked
                if val > r:
                    break
                elif val < l:
                    while firstPicked <= lastPicked and lastPicked < n - 1:
                        lastPicked += 1
                        val += cards[lastPicked]
                        # print("1>", firstPicked, lastPicked, val)
                        if l <= val <= r:
                            picked = lastPicked
                            win_times += 1
                            # print("2.1>", firstPicked, lastPicked, val)
                            break
                        elif val < l:
                            continue
                        while val > r:
                            val -= cards[firstPicked]
                            firstPicked += 1
                            # print("2.2>", firstPicked, lastPicked, val)
                            if l <= val <= r:
                                picked = lastPicked
                                win_times += 1
                                break
                            if firstPicked == lastPicked:
                                picked = lastPicked
                                break
                elif l <= val <= r:
                    picked += 1
                    win_times += 1
                    break
            # print(f"3> p: {picked} | s: {val} | w: {win_times}")
    return win_times


for _ in range(input_to_int()):
    print(solve())
