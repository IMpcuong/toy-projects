from collections import deque


_desired_str = "narek"
_desired_str_len = len(_desired_str)


def cal_maximum_valid_seq_starts_from(idx: int, latest_str: str) -> int:
    actual_validate_str = latest_str[idx:]
    dq = deque()
    ans = 0
    for chr in actual_validate_str:
        if len(dq) == _desired_str_len:
            ans += 1
            dq.clear()
        if len(dq) == 0 and chr == "n":
            dq.appendleft(chr)
            continue
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
            continue
    return ans


if __name__ == "__main__":
    samples = ["nrrareknkarekz", "nnaarreekk"]
    ans = [cal_maximum_valid_seq_starts_from(0, sample) for sample in samples]
    print(*ans)
