# Link: https://codeforces.com/contest/2019/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n, k = input_to_map()
    freq = input_to_list()
    decks = max(freq)
    owned_cards = sum(freq)
    distinct = 1
    if decks == 0:
        return min(n, k)
    for c in range(1, n + 1):
        total_cards = owned_cards + k
        t_decks, m = divmod(total_cards, c)
        if k == 0:
            if m == 0 and t_decks >= decks:
                distinct = c
        else:
            if t_decks >= decks:
                distinct = c
    return distinct


# def solve() -> int:
#     n, k = input_to_map()
#     freq = input_to_list()
#     decks = max(freq)
#     owned_cards = sum(freq)
#     distinct = n
#     if decks == 0:
#         return min(n, k)
#     if k == 0:
#         while owned_cards % decks != 0 and distinct > 1:
#             decks += 1
#         distinct = owned_cards // decks
#         return distinct
#     while distinct * decks - owned_cards > k and distinct > 1:
#         distinct -= 1
#     return distinct


for _ in range(input_to_int()):
    print(solve())
