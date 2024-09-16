# Link: https://codeforces.com/problemset/problem/1791/D

t = int(input())
while t > 0:
    n = int(input())
    s = input()
    uniq = set()
    m = 0

    # Approach 1:
    a = [0] * 26
    for i in range(n):
        a[ord(s[i]) - 97] += 1
    b = [0] * 26
    for i in range(n):
        m_tmp = 0
        idx = ord(s[i]) - 97
        b[idx] += 1
        a[idx] -= 1
        m_tmp = 26 * 2 - (a.count(0) + b.count(0))
        m = max(m, m_tmp)

    # Approach 2:
    # v = [0] * n
    # for i in range(n):
    #     uniq.add(s[i])
    #     v[i] = len(uniq)
    #     if i == n - 1:
    #         uniq = set()
    # for j in range(n - 1, 0, -1):
    #     uniq.add(s[j])
    #     m = max(m, v[j - 1] + len(uniq))

    # Approach 3:
    # for i in range(n):
    #     m_tmp = 0
    #     if s[i] not in uniq:
    #         uniq.add(s[i])
    #         m_tmp = len(set(s[: i + 1])) + len(set(s[i + 1 :]))
    #     m = max(m, m_tmp)
    print(m)
    t -= 1
