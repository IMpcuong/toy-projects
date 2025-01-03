# Link: https://codeforces.com/contest/2005/problem/C

import sys
from collections import deque


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


_desired_str = "narek"
_desired_str_len = len(_desired_str)


def cal_total_appearance_of(chars: str, sample_str: str) -> int:
    appearances = 0
    for chr in chars:
        appearances += sample_str.count(chr)
    return appearances


def cal_maximum_valid_seq_starts_from(idx: int, latest_str: str) -> tuple[int]:
    actual_validate_str = latest_str[idx:]
    dq = deque()
    valid_seq = 0
    rightmost_k_pos = -1
    for i, chr in enumerate(actual_validate_str):
        if len(dq) == 0 and chr == "n":
            dq.appendleft(chr)
        elif 0 < len(dq) < _desired_str_len:
            top = dq[0]
            if top == "n" and chr == "a":
                dq.appendleft(chr)
            elif top == "a" and chr == "r":
                dq.appendleft(chr)
            elif top == "r" and chr == "e":
                dq.appendleft(chr)
            elif top == "e" and chr == "k":
                dq.appendleft(chr)
                rightmost_k_pos = max(rightmost_k_pos, i)
        if len(dq) == _desired_str_len:
            valid_seq += 1
            dq.clear()
    return [valid_seq, rightmost_k_pos]


def solve() -> int:
    total_samples, str_len = input_to_map()
    samples = [input() for _ in range(total_samples)]
    # t := [n, a, r, e, k]
    # + Calculate the total appearances of each letter from t.
    # + Calculate the maximize number which the `_t` set was able to exist.
    dp = [0] * 2
    appearances = 0
    score = 0
    eval_str = ""
    for i in range(total_samples):
        eval_str += samples[i]
        appearances += cal_total_appearance_of(_desired_str, eval_str)
        if i == 0:
            dp[0], dp[1] = cal_maximum_valid_seq_starts_from(0, eval_str)
    # print(dp)
    return 10 * dp[-1][0] - appearances


for _ in range(input_to_int()):
    print(solve())
