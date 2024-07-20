import sys
input = sys.stdin.readline

n = int(input())
lo, hi = 0, 1000000
while lo + 1 < hi:
    mid = lo + hi >> 1
    if pow(6, mid) <= n: lo = mid
    else: hi = mid
print(hi)