import bisect

from collections import defaultdict


int_input = lambda: int(input())

n = int_input()
ks = defaultdict(list)
_ks = [int(x) for x in input().split(' ')]
for i, _k in enumerate(_ks, 1):
    ks[_k].append(i)

m = int_input()
for i in range(m):
    l, r, k = [int(x) for x in input().split(' ')]
    low = bisect.bisect_left(ks[k], l)
    high = bisect.bisect_right(ks[k], r)
    print(high - low)
