# Link: https://codeforces.com/problemset/problem/2004/B

t = int(input())
for _ in range(t):
    l1, r1 = map(int, input().split())
    l2, r2 = map(int, input().split())
    closed = 1
    if r1 == r2 and l1 == l2:
        closed = r1 - l1
    elif r1 == r2 and l1 != l2:
        closed = r1 - max(l1, l2) + 1
    elif r1 != r2 and l1 == l2:
        closed = min(r1, r2) - l1 + 1
    else:
        if r1 == l2 or r2 == l1:
            closed += 1
        elif r1 < l2 or r2 < l1:
            closed += 0
        else:
            closed = min(r1, r2) - max(l1, l2) + 1 + 1
    print(closed)
