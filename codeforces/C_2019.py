# Link: https://codeforces.com/contest/2019/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n, extra_cards = input_to_map()
    freq = input_to_list()
    min_decks = max(freq)
    owned_cards = sum(freq)
    distinct = 1
    for deck_height in range(2, n + 1):
        # remain_cards = owned_cards % i < i (1)
        decks, remain_cards = divmod(owned_cards, deck_height)
        if decks < min_decks:
            if extra_cards == 0:
                continue
            # k % i < i (2)
            # (1) + (2) -> remain_cards + k % i < 2 * i
            if remain_cards + extra_cards % deck_height >= deck_height:
                decks += 1
            needed_decks = min_decks - decks
            extra_decks = extra_cards // deck_height
            if extra_decks < needed_decks:
                continue
            distinct = deck_height
        else:
            if remain_cards == 0:
                distinct = deck_height
            else:
                if deck_height - remain_cards <= extra_cards:
                    distinct = deck_height
    return distinct


for _ in range(input_to_int()):
    print(solve())
