# https://codeforces.com/problemset/problem/1932/A

t = int(input())
while t > 0:
    n = int(input())
    s = input()
    print(s[: s.find("**")].count("@") if s.find("**") != -1 else s.count("@"))
    t -= 1
