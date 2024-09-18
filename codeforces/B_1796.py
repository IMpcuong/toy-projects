# Link: https://codeforces.com/problemset/problem/1796/B

t = int(input())
while t > 0:
    a = input()
    b = input()
    if a[0] == b[0] and a[-1] == b[-1]:
        print("YES")
        print(f"{a[0]}*")
    elif a[0] == b[0]:
        print("YES")
        print(f"{a[0]}*")
    elif a[-1] == b[-1]:
        print("YES")
        print(f"*{a[-1]}")
    else:
        exist_sub_seq = False
        sub_seq = ""
        for i in range(len(a) - 1):
            s = a[i] + a[i + 1]
            if s in b:
                exist_sub_seq = True
                sub_seq = s
                break
        if exist_sub_seq:
            print("YES")
            print(f"*{sub_seq}*")
        else:
            print("NO")
    t -= 1
