# Link: https://codeforces.com/contest/2019/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n, k = input_to_map()
    freq = input_to_list()
    min_decks = max(freq)
    owned_cards = sum(freq)
    distinct = 1
    for i in range(2, n + 1):
        # remain_cards = owned_cards % i < i (1)
        decks, remain_cards = divmod(owned_cards, i)
        if decks < min_decks:
            if k == 0:
                continue
            # k % i < i (2)
            # (1) + (2) -> remain_cards + k % i < 2 * i
            if remain_cards + k % i >= i:
                decks += 1
            needed = min_decks - decks
            extra = k // i
            if extra < needed:
                continue
            distinct = i
        else:
            if remain_cards == 0:
                distinct = i
            else:
                if i - remain_cards <= k:
                    distinct = i
    return distinct


for _ in range(input_to_int()):
    print(solve())
