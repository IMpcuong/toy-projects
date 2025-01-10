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
        if chr == "n":
            if len(dq) == 0:
                dq.appendleft(chr)
            else:
                prev_bot_score += 1
        elif 0 < len(dq) < _desired_str_len:
            top = dq[0]
            if top == "n" and chr == "a":
                if len(dq) == 2:
                    prev_bot_score += 1
                    continue
                dq.appendleft(chr)
            elif top == "a" and chr == "r":
                if len(dq) == 3:
                    prev_bot_score += 1
                    continue
                dq.appendleft(chr)
            elif top == "r" and chr == "e":
                if len(dq) == 4:
                    prev_bot_score += 1
                    continue
                dq.appendleft(chr)
            elif top == "e" and chr == "k":
                if len(dq) == 5:
                    prev_bot_score += 1
                    continue
                dq.appendleft(chr)
        if len(dq) == _desired_str_len:
            prev_human_score += 5
            dq.clear()
        if counter == len(next_sample) and 0 < len(dq) < _desired_str_len:
            dq.reverse()
            prev_tail = "".join(dq)
    return (prev_human_score, prev_bot_score, prev_tail)


if __name__ == "__main__":
    samples = ["nrrareknkarekz", "nnaarreekk", "narek", "nare"]
    ans = [cal_maximum_valid_seq_starts_from(0, 0, "", sample) for sample in samples]
    print(*ans)
