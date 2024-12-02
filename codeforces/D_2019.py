# Link: https://codeforces.com/problemset/problem/2019/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def search_all_interval_ranges(deadlines: list[int]) -> dict:
    ans = dict()
    for i, moment in enumerate(deadlines):
        if moment not in ans:
            ans[moment] = []
        ans[moment].append(i)
    for moment in ans:
        first = ans[moment][0]
        last = ans[moment][-1]
        ans[moment] = [first, last]
    return ans


def solve() -> list[int]:
    n = input_to_int()
    conquer_times = input_to_list()
    desc_deadlines = sorted(list(set(conquer_times)), reverse=True)
    map_deadline = search_all_interval_ranges(conquer_times)
    for moment in map_deadline:
        leftmost_idx, rightmost_idx = map_deadline[moment]
        cur_distance = rightmost_idx - leftmost_idx + 1
        if cur_distance > moment:
            return 0
        if leftmost_idx <= rightmost_idx:
            tmp_lm = rightmost_idx - (moment - 1)
            tmp_rm = leftmost_idx + (moment - 1)
            if tmp_lm >= 0:
                leftmost_idx = tmp_lm
            else:
                leftmost_idx = 0
            if tmp_rm < n:
                rightmost_idx = tmp_rm
            else:
                rightmost_idx = n - 1
        map_deadline[moment] = [leftmost_idx, rightmost_idx]
    lo, ro = 0, 0
    for i, moment in enumerate(desc_deadlines):
        if i == 0:
            lo = map_deadline[moment][0]
            ro = map_deadline[moment][1]
        else:
            ln = map_deadline[moment][0]
            rn = map_deadline[moment][1]
            kn = moment - 1
            if ln >= lo and rn >= ro:
                if ln + kn > ro:
                    return 0
                else:
                    ln = ln
                    rn = ro
            elif ln <= lo and rn <= ro:
                if rn - kn < lo:
                    return 0
                else:
                    ln = lo
                    rn = rn
            elif lo >= ln and ro <= rn:
                ln = lo
                rn = ro
            elif lo <= ln and ro >= rn:
                ln = ln
                rn = rn
            lo = ln
            ro = rn
    return ro - lo + 1


for _ in range(input_to_int()):
    print(solve())
