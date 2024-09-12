# Link: https://codeforces.com/problemset/problem/1900/B

t = int(input())
l = 3
while t > 0:
    digits = list(map(int, input().split()))
    # if len(set(digits)) == 1:
    #     digits = [1, 1, 1]
    # if len(set(digits)) == 2:
    #     freq = [digits.count(n) for n in digits]
    #     a = [i for i, f in enumerate(freq) if f == min(freq)]
    #     digits = [0] * l
    #     digits[a[0]] = 1
    # if len(set(digits)) == 3:
    sum_by_others_fn_once = lambda a: [sum(a) - x for x in a if isinstance(a, list)]
    a = sum_by_others_fn_once(digits)
    digits = [(1 - n % 2) for n in a]
    print(*digits)
    t -= 1
