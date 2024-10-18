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
    distinct = n
    if k == 0:
        if 2 * decks == owned_cards:
            return 2
        return 1
    while distinct * decks - owned_cards > k and distinct > 1:
        distinct -= 1
    return distinct


for _ in range(input_to_int()):
    print(solve())
