# Link: https://codeforces.com/problemset/problem/1809/B
# Link: https://codeforces.com/blog/entry/114300

t = int(input())
while t > 0:
    chips = int(input())
    # NOTE: Built-in := math.isqrt(chips).
    sr = int((chips + 1) ** 0.5)
    print(sr - 1 if sr ** 2 >= chips else sr)
    t -= 1
