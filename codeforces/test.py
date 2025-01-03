from collections import deque


_desired_str = "narek"
_desired_str_len = len(_desired_str)


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
                print(i)
                print(rightmost_k_pos)
                rightmost_k_pos = max(rightmost_k_pos, i)
        if len(dq) == _desired_str_len:
            valid_seq += 1
            dq.clear()
    return [valid_seq, rightmost_k_pos]


if __name__ == "__main__":
    samples = ["nrrareknkarekz", "nnaarreekk", "narek", "nare"]
    ans = [cal_maximum_valid_seq_starts_from(0, sample) for sample in samples]
    print(*ans)
