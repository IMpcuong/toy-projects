# Link: https://codeforces.com/contest/2005/problem/C

import math
import sys
from collections import deque


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


_desired_str = "narek"
_desired_str_len = len(_desired_str)
_inf_val = math.inf


def cal_total_appearance_of(chars: str, sample_str: str) -> int:
    appearances = 0
    for chr in chars:
        appearances += sample_str.count(chr)
    return appearances


def cal_optimal_scores(
    prev_human_score: int, prev_bot_score: int, prev_tail: str, next_sample: str
) -> tuple:
    dq = deque()
    if len(prev_tail) > 0:
        reverse_prev_tail = prev_tail[::-1]
        dq.extendleft(reverse_prev_tail)
    counter = 0
    for chr in next_sample:
        counter += 1
        if len(dq) == 0:
            if chr == "n":
                dq.appendleft(chr)
            elif chr == "a" or chr == "r" or chr == "e" or chr == "k":
                prev_bot_score += 1
        elif len(dq) < _desired_str_len:
            top = dq[0]
            for target_chr_pos in range(_desired_str_len - 1):
                target_chr = _desired_str[target_chr_pos]
                next_target_chr = _desired_str[target_chr_pos + 1]
                if top == target_chr:
                    if chr == next_target_chr:
                        dq.appendleft(chr)
                    elif chr != next_target_chr and chr in _desired_str:
                        prev_bot_score += 1
        if len(dq) == _desired_str_len:
            prev_human_score += _desired_str_len
            dq.clear()
    if counter == len(next_sample) and 0 < len(dq) < _desired_str_len:
        prev_bot_score += len(dq)
        dq.reverse()
        prev_tail = "".join(dq)
    return (prev_human_score, prev_bot_score, prev_tail)


def cal_final_score_per_state(human_score: int, bot_score: int) -> int:
    cur_score = human_score - bot_score
    if cur_score > 0:
        return cur_score
    return 0


def solve() -> int:
    total_samples, _ = input_to_map()
    samples = [input() for _ in range(total_samples)]
    # t := [n, a, r, e, k]
    # + Calculate the total appearance of each letter from t.
    # + Calculate the maximize number which the `_desired_str` sequence was able to exist.
    dp = {"nare": 0, "nar": 0, "na": 0, "n": 0, "empty": 0}
    prev_human_score, prev_bot_score, prev_tail = 0, 0, ""
    for i in range(total_samples):
        human_score, bot_score, tail = cal_optimal_scores(
            prev_human_score, prev_bot_score, prev_tail, samples[i]
        )
        cur_score = cal_final_score_per_state(human_score, bot_score)
        print(">>>>>", human_score, bot_score, cur_score, tail)
        if tail == "":
            if cur_score > dp["empty"]:
                dp["empty"] += cur_score
                prev_human_score += human_score
                prev_bot_score += bot_score
                prev_tail = tail
        else:
            if cur_score > dp[tail]:
                dp[tail] += cur_score
                prev_human_score += human_score
                prev_bot_score += bot_score
                prev_tail = tail
    return max(dp.values())


for _ in range(input_to_int()):
    print(solve())
