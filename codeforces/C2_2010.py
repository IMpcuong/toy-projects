# Link: https://codeforces.com/problemset/problem/2010/C2

m = input()
n = len(m)
if len(m) == 1:
    print("NO")
    exit()
l_m1, l_m2 = 0, 0
first_m1 = m[0]
j = 1
count_d, count_f = 0, 0
for i, c in enumerate(m):
    if c != first_m1:
        j += 1
    if m[j] == first_m1:
        count_f += 1
        if j == 1 and len(set(m)) > 1:
            continue
        if m[:j] == m[i : i + j]:
            count_d += 1
            if i + j < n:
                l_m1 = n - 2 * j
                l_m2 = j - l_m1
            else:
                l_m1 = 0
            if count_f - count_d == 1:
                break
    else:
        j = i + 1
print(l_m1, l_m2, count_f, count_d)
if l_m1 > 0:
    print("YES")
    print(m[: 2 * l_m1 - l_m2])
    print(m[: 2 * l_m1 + l_m2])
else:
    print("NO")
