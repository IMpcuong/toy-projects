# Link: https://codeforces.com/problemset/problem/1918/B

t = int(input())
while t > 0:
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    zipped = list(zip(a, b))
    zipped.sort()  # NOTE: Sorting based on the first element of the tuple.
    p1 = [tup[0] for tup in zipped]
    p2 = [tup[1] for tup in zipped]
    print(*p1)
    print(*p2)
    t -= 1
