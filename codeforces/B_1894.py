# Link: https://codeforces.com/problemset/problem/1894/B

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    s = set(a)
    # freq = [0] * (max(a) + 1)
    # for i in a:
    #     freq[i] += 1
    # distinct = 0
    # for e in freq:
    #     distinct += 1 if e > 1 else 0
    distinct = 0
    flag = True
    b = [1] * n
    for e in s:
        if a.count(e) > 1:
            distinct += 1
        # NOTE: The operation only be executed twice (the first 2 numbers).
        if flag and a.count(e) > 1:
            b[a.index(e)] = 2
            flag = False
            continue
        if not flag and a.count(e) > 1:
            b[a.index(e)] = 3
            break
    if distinct >= 2:
        print(*b)
    else:
        print(-1)
