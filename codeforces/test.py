from collections import deque


_desired_str = "narek"
_desired_str_len = len(_desired_str)


def cal_maximum_valid_seq_starts_from(
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
            # if top == "n":
            #     if chr == "a":
            #         dq.appendleft(chr)
            #     elif chr == "n" or chr == "r" or chr == "e" or chr == "k":
            #         prev_bot_score += 1
            # elif top == "a":
            #     if chr == "r":
            #         dq.appendleft(chr)
            #     elif chr == "n" or chr == "a" or chr == "e" or chr == "k":
            #         prev_bot_score += 1
            # elif top == "r":
            #     if chr == "e":
            #         dq.appendleft(chr)
            #     elif chr == "n" or chr == "a" or chr == "r" or chr == "k":
            #         prev_bot_score += 1
            # elif top == "e":
            #     if chr == "k":
            #         dq.appendleft(chr)
            #     elif chr == "n" or chr == "a" or chr == "r" or chr == "e":
            #         prev_bot_score += 1
        if len(dq) == _desired_str_len:
            prev_human_score += _desired_str_len
            dq.clear()
    if counter == len(next_sample) and 0 < len(dq) < _desired_str_len:
        prev_bot_score += len(dq)
        dq.reverse()
        prev_tail = "".join(dq)
    return (prev_human_score, prev_bot_score, prev_tail)


if __name__ == "__main__":
    samples = ["nrrareknkarekz", "nnaarreekk", "narek", "nare"]
    ans = [cal_maximum_valid_seq_starts_from(0, 0, "", sample) for sample in samples]
    print(*ans)
