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
    map_timeline = dict()
    for time in conquer_times:
        if time not in map_timeline:
            map_timeline[time] = []
        map_timeline[time] = search_interval_range(conquer_times, time)
    return map_timeline


for _ in range(input_to_int()):
    print(solve())
