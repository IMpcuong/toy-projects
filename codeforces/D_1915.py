# Link: https://codeforces.com/problemset/problem/1915/D

t = int(input())
while t > 0:
    n = int(input())
    s = list(input())
    vowels = ["a", "e"]
    for i in range(2, n):  # s[0] + s[1] ~ CV
        if s[i] in vowels:
            s[i - 1] = "." + s[i - 1]
    print("".join(s))
    t -= 1
