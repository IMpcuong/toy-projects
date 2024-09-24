# Link: https://codeforces.com/problemset/problem/2008/D

t = int(input())
while t > 0:
    n = int(input())
    p = list(map(int, input().split()))
    s = input()
    ans = [0] * n
    visited = [False] * n
    for i in range(n):
        cur = i
        path = []
        # NOTE: non-directed graph, node[i] -> node[j] through n nodes, the reverse path is identical.
        if visited[i]:
            continue
        while not visited[cur]:
            path.append(cur)
            visited[cur] = True
            cur = p[cur] - 1
        count = 0
        for r in path:
            if s[r] == "0":
                # ans[i] += 1
                count += 1
        for r in path:
            ans[r] = count
    print(*ans)
    t -= 1
