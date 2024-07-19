# Link: https://codeforces.com/problemset/problem/1978/A

t = int(input())
for _ in range(t):
    books = int(input())
    pages = list(map(int, input().split()))
    print(pages[books - 1] + max(pages[: books - 1]))
