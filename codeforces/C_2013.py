# Link: https://codeforces.com/contest/2013/problem/C

import sys
from typing import Deque


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())
send_fmt_query = lambda sign, s: print(
    f"{sign} {''.join(map(str, s))}", sep="", flush=True
)


def ask(s: Deque) -> bool:
    send_fmt_query("?", s)
    return input() == "1"


def answer(s: Deque) -> str:
    send_fmt_query("!", s)


from collections import deque


def solve():
    n = input_to_int()
    dq = deque()
    # NOTE: Cannot go further than the leftmost character.
    while len(dq) < n:
        dq.appendleft("0")  # dq[0] = "0"
        if not ask(dq):
            dq[0] = "1"
            if not ask(dq):
                dq.popleft()
                break
    # NOTE: Turn around + head to the rightmost character.
    while len(dq) < n:
        dq.append("0")  # dq[-1] = "0"
        if not ask(dq):
            dq[-1] = "1"
    answer(dq)


for _ in range(input_to_int()):
    solve()
