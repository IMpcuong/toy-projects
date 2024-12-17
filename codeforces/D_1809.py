# Link: https://codeforces.com/contest/1809/problem/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


_invalid_state = -1


def set_current_step_cost(
    dp_state: dict[str, int], cur_tail: str, cur_cost: int
) -> None:
    if dp_state[cur_tail] == _invalid_state:
        dp_state[cur_tail] = cur_cost
    else:
        if dp_state[cur_tail] > cur_cost:
            dp_state[cur_tail] = cur_cost


def solve() -> int:
    bin_str = input()
    l = len(bin_str)
    _cost = int(1e12)
    if l == 1:
        return 0
    if l == 2:
        if bin_str == "10":
            return _cost
        else:
            return 0
    get_min_cost_from = lambda dp: min([v for v in dp.values() if v != _invalid_state])
    dp = {"00": _invalid_state, "01": _invalid_state, "11": _invalid_state}
    first_char = bin_str[0]
    second_char = bin_str[1]
    third_char = bin_str[2]
    starting_state = first_char + second_char
    next_step = 0
    if starting_state == "00":
        if third_char == 0:
            dp["00"] = 0  # 000 -> 000
        else:
            dp["00"] = _cost + 1  # 001 -> 00 ~ delete
            dp["01"] = 0  # 001 -> 001
        next_step = 3
    elif starting_state == "01":
        if third_char == "0":
            dp["01"] = _cost  # 010 -> 001 ~ swap
            dp["00"] = _cost  # 010 -> 00 ~ delete
        else:
            dp["11"] = 0  # 011 -> 011
            dp["01"] = _cost  # 011 -> 01 ~ delete
        next_step = 3
    elif starting_state == "11":
        if third_char == "0":
            dp["11"] = _cost + 1  # 110 -> 11 ~ delete
        else:
            dp["11"] = 0  # 111 -> 111
        next_step = 3
    elif starting_state == "10":
        if third_char == "0":
            dp["00"] = _cost + 1  # 100 -> 00 ~ delete
        else:
            dp["11"] = _cost  # 101 -> 011 ~ swap
            dp["01"] = _cost + 1  # 101 -> 01 ~ delete
        next_step = 3
    for i in range(next_step, l):
        cur_char = bin_str[i]
        dp_tmp = {"00": _invalid_state, "01": _invalid_state, "11": _invalid_state}
        if cur_char == "0":
            # prev_tail == 00
            if dp["00"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="00", cur_cost=dp["00"]
                )  # 000 -> 000
            # prev_tail == 01
            if dp["01"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="01", cur_cost=dp["01"] + _cost
                )  # 010 -> 001 ~ swap
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="00", cur_cost=dp["01"] + _cost + 1
                )  # 010 -> 00 ~ delete
            # prev_tail == 11:
            if dp["11"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="11", cur_cost=dp["11"] + _cost + 1
                )  # 110 -> 11 ~ delete
        elif cur_char == "1":
            # prev_tail == 00
            if dp["00"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="01", cur_cost=dp["00"]
                )  # 001 -> 001
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="00", cur_cost=dp["00"] + _cost + 1
                )  # 001 -> 00 ~ delete
            # prev_tail == 01
            if dp["01"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="11", cur_cost=dp["01"]
                )  # 011 -> 011
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="01", cur_cost=dp["01"] + _cost + 1
                )  # 011 -> 01 ~ swap
            # prev_tail == 11:
            if dp["11"] != _invalid_state:
                set_current_step_cost(
                    dp_state=dp_tmp, cur_tail="11", cur_cost=dp["11"]
                )  # 111 -> 111
        dp = dp_tmp
    ans = get_min_cost_from(dp)
    return ans


for _ in range(input_to_int()):
    print(solve())
