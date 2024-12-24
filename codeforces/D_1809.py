# Link: https://codeforces.com/contest/1809/problem/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


_invalid_val = 1e20 + 1
_cost_swap = int(1e12)
_cost_erase = _cost_swap + 1


def calc_optimal_cost_for_state(costs_per_state: list[int]) -> list[int]:
    ans = []
    length = len(costs_per_state)
    for i in range(0, length, 3):
        ans.append(
            min(costs_per_state[i], costs_per_state[i + 1], costs_per_state[i + 2])
        )
    return ans


def indicate_valid_min_cost(final_state_dict: dict[str, int]) -> int:
    valid_dict = {k: v for k, v in final_state_dict.items() if v != _invalid_val}
    return min(valid_dict.values())


def solve() -> int:
    bin_str = input()
    str_len = len(bin_str)
    ans = 0
    dp = {
        "empty": 0,
        "0": _invalid_val,
        "1": _invalid_val,
        "00": _invalid_val,
        "01": _invalid_val,
        "11": _invalid_val,
    }
    for i in range(str_len):
        digit = bin_str[i]
        # NOTE:
        # + "0" ~ 0->2
        # + "1" ~ 3->5
        # + "00" ~ 6->8
        # + "01" ~ 9->11
        # + "11" ~ 12->14
        tmp_val_list = [_invalid_val] * 15
        if digit == "0":
            tmp_val_list[0] = dp["empty"]
            tmp_val_list[1] = dp["0"] + _cost_erase  # 00 -> 0
            tmp_val_list[2] = dp["1"] + _cost_erase  # 10 -> 0

            tmp_val_list[4] = dp["1"] + _cost_erase  # 10 -> 1

            tmp_val_list[6] = dp["0"]
            tmp_val_list[7] = dp["00"]  # 000 -> 00
            tmp_val_list[8] = dp["01"] + _cost_erase  # 010 -> 00

            tmp_val_list[9] = dp["1"] + _cost_swap  # 10 -> 01
            tmp_val_list[10] = dp["01"] + _cost_swap  # 10 -> 01

            tmp_val_list[12] = dp["11"] + _cost_erase  # 110 -> 11
        elif digit == "1":
            tmp_val_list[0] = dp["0"] + _cost_erase  # 01 -> 0

            tmp_val_list[3] = dp["empty"]
            tmp_val_list[4] = dp["0"] + _cost_erase  # 01 -> 1
            tmp_val_list[5] = dp["1"] + _cost_erase  # 11 -> 1

            tmp_val_list[6] = dp["00"] + _cost_erase  # 001 -> 00

            tmp_val_list[9] = dp["0"]
            tmp_val_list[10] = dp["00"]  # 001 -> 01
            tmp_val_list[11] = dp["01"] + _cost_erase  # 011 -> 01

            tmp_val_list[12] = dp["1"]  # 11 -> 11
            tmp_val_list[13] = dp["11"]  # 111 -> 11
            tmp_val_list[14] = dp["01"]  # 011 -> 11
        optimal_vals = calc_optimal_cost_for_state(tmp_val_list)
        dp["0"] = optimal_vals[0]
        dp["1"] = optimal_vals[1]
        dp["00"] = optimal_vals[2]
        dp["01"] = optimal_vals[3]
        dp["11"] = optimal_vals[4]
        dp["empty"] = dp["empty"] + _cost_erase
    ans = indicate_valid_min_cost(dp)
    return ans


for _ in range(input_to_int()):
    print(solve())
