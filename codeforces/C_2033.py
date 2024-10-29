# Link: https://codeforces.com/contest/2019/problem/C

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    topics = input_to_list()
    dp = [0] * 2
    for i in range(n // 2):
        if i == 0:
            dp[0] = 0 # cur switch
            dp[1] = 0 # cur stay
        else:
            leftmost = i
            prev_leftmost = leftmost - 1
            rightmost = n - i - 1
            prev_rightmost = rightmost + 1

            switch_switch, switch_stay = dp[0], dp[0]
            # cur switch -> prev stay || prev switch
            # 1> cur switch + prev stay
            if topics[rightmost] == topics[prev_leftmost]:
                switch_stay += 1
            if topics[leftmost] == topics[prev_rightmost]:
                switch_stay += 1
            # 2> cur switch + prev switch
            if topics[leftmost] == topics[prev_leftmost]:
                switch_switch += 1
            if topics[rightmost] == topics[prev_rightmost]:
                switch_switch += 1
            # print("1>>>>>", i, switch_switch, switch_stay)
            dp[0] = min(switch_switch, switch_stay)

            stay_stay, stay_switch = dp[1], dp[1]
            # cur stay -> prev stay || prep switch
            # 1> cur stay + prev stay
            if topics[leftmost] == topics[prev_leftmost]:
                stay_stay += 1
            if topics[rightmost] == topics[prev_rightmost]:
                stay_stay += 1
            # 2> cur stay + prev switch
            if topics[leftmost] == topics[prev_rightmost]:
                stay_switch += 1
            if topics[rightmost] == topics[prev_leftmost]:
                stay_switch += 1
            # print("2>>>>>", i, stay_switch, stay_stay)
            dp[1] = min(stay_switch, stay_stay)
    if n % 2 == 0:
        if topics[n // 2 - 1] == topics[n // 2]:
            dp[0] += 1
            dp[1] += 1
    else:
        if topics[n // 2] == topics[n // 2 - 1] == topics[n // 2 + 1]:
            dp[0] += 2
            dp[1] += 2
        elif topics[n // 2] == topics[n // 2 - 1] or topics[n // 2] == topics[n // 2 + 1]:
            dp[0] += 1
            dp[1] += 1
    return min(dp[0], dp[1])


for _ in range(input_to_int()):
    print(solve())
