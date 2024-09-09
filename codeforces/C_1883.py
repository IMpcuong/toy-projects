# Link: https://codeforces.com/problemset/problem/1883/C

from typing import List, Tuple


def find_optimal_ops(k: int, n: int, arr: List[int]) -> int:
    # NOTE: len(arr) == n > 0.
    min_d = (k - arr[0] % k) if arr[0] % k != 0 else 0
    if n == 1:
        return min_d
    for num in arr:
        if num % k == 0:
            return 0
        d = k - num % k
        if d < min_d:
            min_d = d
    return min_d


t = int(input())
while t > 0:
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    ops = find_optimal_ops(k=k, n=n, arr=arr)
    if k == 4:
        ops_4 = 0
        count = 0
        for i in range(n):
            if arr[i] % 2 != 0:
                count += 1
        if n - count == 0:
            # NOTE: arr[i] mod 4 == 1.
            ops_4 = 2
            # NOTE: arr[i] mod 4 == 3 -> wrapped at line 24.
        elif n - count == 1:
            ops_4 = 1
        # elif n - count > 1:
        #     ops_4 = 0
        ops = min(ops, ops_4)
    print(ops)
    t -= 1
