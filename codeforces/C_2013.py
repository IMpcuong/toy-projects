# Link: https://codeforces.com/contest/2013/problem/C

import sys

input = lambda: sys.stdin.readline().rstrip()
input_to_int = lambda: int(input())
input_to_map = lambda: map(int, input().split())
input_to_list = lambda: list(input_to_map())
fmt_query = lambda sign, str: print(f"{sign} {str}", sep="", flush=True)

t = int(input())
while t > 0:
    n = int(input())
    ans = ""
    if n == 1:
        fmt_query("?", "0")
        if input() == "1":
            ans = "0"
        else:
            ans = "1"
        fmt_query("!", ans)
        continue
    addRight = False
    ans1 = "01" + ans
    ans2 = "10" + ans
    fmt_query("?", ans1)
    r1 = input()
    r2 = "0"
    if r1 == "1":
        ans = ans1
    else:
        fmt_query("?", ans2)
        r2 = input()
        if r2 == "1":
            ans = ans2
    if r1 == "1" or r2 == "1":
        while len(ans) < n:
            if not addRight:
                fmt_query("?", "0" + ans)
                if input() == "1":
                    ans = "0" + ans
                else:
                    fmt_query("?", "1" + ans)
                    if input() == "1":
                        ans = "1" + ans
                    else:
                        addRight = True
            else:
                fmt_query("?", ans + "0")
                if input() == "1":
                    ans = ans + "0"
                else:
                    fmt_query("?", ans + "1")
                    if input() == "1":
                        ans = ans + "1"
        fmt_query("!", ans)
    else:
        ans = "0" * n
        fmt_query("?", ans)
        if input() == "1":
            fmt_query("!", ans)
        else:
            ans = "1" * n
            fmt_query("!", ans)
    t -= 1