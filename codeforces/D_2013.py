# Link: https://codeforces.com/contest/2013/problem/D

import sys


input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())


def solve() -> int:
    n = input_to_int()
    a = input_to_list()
    if n == 1:
        return 0
    if n == 2:
        if a[0] == a[1]:
            return 0
        elif a[0] < a[1]:
            return a[1] - a[0]
        return (a[0] - a[1]) % 2
    # NOTE: The stack only got 2 forms after any steps of balancing:
    #   + stack = [(n + m), a]
    #   + stack = [(n, a), (m, a + 1)]
    stack = []
    for i in range(n):
        cur_c, cur_v = 1, a[i]
        while stack and a[i] < stack[-1][1]:
            s_c, s_v = stack.pop()
            cur_c += s_c
            cur_v += s_c * s_v
            a[i] = cur_v // cur_c
        a[i], remain = divmod(cur_v, cur_c)
        if remain == 0:
            stack.append([cur_c, a[i]])
        # NOTE:
        # + Given conditions:
        #   cur_v = a[i] * cur_c + remain
        #   cur_c = n + m
        # + After balancing:
        #   stack := [(n, a[i]), (m, a[i] + 1)]
        #   n * a[i] + m * (a[i] + 1) = cur_v
        #     <-> (n + m) * a[i] + m = cur_v
        #     <-> cur_c * a[i] + m = a[i] * cur_c + remain
        #     <-> m = remain && n = cur_c - remain
        if remain > 0:
            stack.append([cur_c - remain, a[i]])
            stack.append([remain, a[i] + 1])  # NOTE: cur_v = a[i] * cur_c + remain
        # print("1>", stack)
    return stack[-1][1] - stack[0][1]


for _ in range(input_to_int()):
    print(solve())
