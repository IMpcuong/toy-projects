# Link: https://codeforces.com/problemset/problem/2019/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def search_interval_range(nums: list[int], target: int) -> list[int]:
    if nums.count(target) == 1:
        pos = nums.index(target)
        return [pos, pos]
    first, last = -1, -1
    for i in range(len(nums)):
        if nums[i] == target:
            if first == -1:
                first = i
            last = i
    return [first, last]


def solve() -> list:
    n = input_to_int()
    conquer_times = input_to_list()
    desc_deadlines = sorted(list(set(conquer_times)), reverse=True)
    map_deadline = dict()
    for moment in conquer_times:
        if moment not in map_deadline:
            map_deadline[moment] = []
        leftmost_idx, rightmost_idx = search_interval_range(conquer_times, moment)
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
    lo, ro, ko = 0, 0, 0
    for i, moment in enumerate(desc_deadlines):
        if i == 0:
            lo = map_deadline[moment][0]
            ro = map_deadline[moment][1]
            ko = moment - 1
        else:
            ln = map_deadline[moment][0]
            rn = map_deadline[moment][1]
            kn = moment - 1
            # print(">>>>>", kn, ln, rn)
            if ln >= lo and rn >= ro:
                if ln + kn > ro:
                    return 0
                else:
                    rn = ro
                    if lo + ko >= ln + kn:
                        ln = lo
                    else:
                        ln = ln + kn - ko
            elif ln <= lo and rn <= ro:
                if rn - kn < 0:
                    return 0
                else:
                    ln = lo
                    if rn -kn <= ro - ko:
                        rn = ro
                    else:
                        rn = rn - kn + ko
            elif lo >= ln and ro <= rn:
                ln = lo
                rn = ro
            elif lo <= ln and ro >= rn:
                if lo + ko >= ln + kn:
                    ln = lo
                else:
                    ln = ln + kn - ko
                if ro - ko <= rn + kn:
                    rn = ro
                else:
                    rn = rn - kn + ko
            lo = ln
            ro = rn
            ko = kn
        print(i, ko, lo, ro)
    return ro - lo + 1


for _ in range(input_to_int()):
    print(solve())
