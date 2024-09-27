# Link: https://codeforces.com/problemset/problem/2003/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> str:
    n = input_to_int()
    s = input()
    freq = [0] * 26
    for rune in s:
        freq[ord(rune) - ord("a")] += 1
    ans = ""  # NOTE: ans ~ "abcdeabcdeabc".
    selected = 0
    while selected < n:
        for i in range(26):
            if freq[i] > 0:
                ans += chr(ord("a") + i)
                freq[i] -= 1
                selected += 1
    return ans


for _ in range(input_to_int()):
    print(solve())
