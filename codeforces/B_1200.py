# Link: https://codeforces.com/problemset/problem/1200/B

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> bool:
    cols, bag_blocks, k = input_to_map()
    heights = input_to_list()
    if cols == 1:
        return True
    for col in range(cols - 1):
        h_cur = heights[col]
        h_next = heights[col + 1]
        lower_bound = max(0, h_next - k)
        if h_cur >= h_next:
            bag_blocks += h_cur - lower_bound
        else:
            if lower_bound > h_cur:
                bag_blocks -= lower_bound - h_cur
            else:
                bag_blocks += h_cur - lower_bound
        if bag_blocks < 0:
            return False
    return True


for _ in range(input_to_int()):
    print("YES" if solve() else "NO")
