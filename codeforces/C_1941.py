# Link: https://codeforces.com/problemset/problem/1941/C

t = int(input())
while t > 0:
    n = int(input())
    s = input()
    print(s.count("map") + s.count("pie") - s.count("mapie"))
    t -= 1