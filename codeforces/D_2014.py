# Link: https://codeforces.com/problemset/problem/2014/D

import sys
from collections import deque
from queue import PriorityQueue


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> list:
    n, d, k = input_to_map()
    jobs = []
    minus_one = lambda x: [x[0] - 1, x[1] - 1]
    for _ in range(k):
        j = minus_one(input_to_list())
        jobs.append(j)
    jobs.sort(key=lambda x: x[0])
    jobs = deque(jobs)
    pq = PriorityQueue(maxsize=k)
    upper_window = 1 + n - d  # NOTE: The iteration always >= 1, whether n == d or not.

    # NOTE: Any range [l, r] can be treated as an overlap to [i, i + d] if it satisfied this 2 constraints simultaneously:
    #   + l < i + d.
    #   + r > i.
    overlap = [0] * upper_window
    # NOTE: The primary technique is slicing window
    #   -> Slip/slide to the left with the range of d (or [i, i + d]) inclusive.
    for i in range(upper_window):
        while len(jobs) > 0:
            j = jobs[0]
            # NOTE: j[0] ~ left && j[1] ~ right -> j := [l, r].
            if j[0] < i + d:
                pq.put(j[1])
                # NOTE: deque.popleft() ~ O(1) < list.pop(0) ~ O(N).
                jobs.popleft()
            else:
                break
        while not pq.empty():
            r = pq.queue[0]
            if r < i:
                pq.get()
            else:
                break
        overlap[i] = pq.qsize()
    b, m = overlap.index(max(overlap)) + 1, overlap.index(min(overlap)) + 1
    return b, m


for _ in range(input_to_int()):
    print(*solve())
