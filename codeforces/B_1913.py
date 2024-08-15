# Link: https://codeforces.com/problemset/problem/1913/B

t = int(input())
while t > 0:
    s = input()
    binary_counter = [0, 0]
    for rune in s:
        binary_counter[int(rune)] += 1
    for i in range(len(s) + 1):
        if i == len(s) or binary_counter[1 - int(s[i])] == 0:
            print(len(s) - i)
            break
        binary_counter[1 - int(s[i])] -= 1
    t -= 1
