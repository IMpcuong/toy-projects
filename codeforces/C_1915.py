# Link: https://codeforces.com/problemset/problem/1915/C


def binary_search(l, r) -> bool:
    if r < 1:
        return True
    while l <= r:
        m = (l + r) // 2
        square = m * m
        if square == s:
            return True
        elif square > s:
            r = m - 1
        else:
            l = m + 1
    return False


t = int(input())
while t > 0:
    nums = int(input())
    s = sum(list(map(int, input().split())))
    l, r = 1, s // 2
    print("YES" if binary_search(l, r) else "NO")
    t -= 1
