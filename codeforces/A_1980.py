# Link: https://codeforces.com/problemset/problem/1980/A

base_difficulty = ["A", "B", "C", "D", "E", "F", "G"]
t = int(input())
for _ in range(t):
    probs, rounds = list(map(int, input().split()))
    difficulties = input()
    freq = [0] * 7
    count = 0
    for ch in difficulties:
        freq[ord(ch) - ord("A")] += 1
    for b in base_difficulty:
        if freq[ord(b) - ord("A")] == 0:
            count += rounds
        elif freq[ord(b) - ord("A")] < rounds:
            count += rounds - freq[ord(b) - ord("A")]
    print(count)
