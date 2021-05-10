import sys
import queue
from math import log

for id in range(1,12): 
    print("now ",id)
    with open("../data/{}.in".format(id),"r") as f: 
        n, m = f.readline().split(" ")
        n, m = int(n), int(m)
        assert(n <= 1e5 and m <= 1e5)

        while( m ):
            m -= 1
            vals = f.readline().split(" ")
            vals = [int(v) for v in vals]
            if vals[0] == 0:
                assert(len(vals) == 4)
                assert(1 <= vals[1] <= vals[2] <= n)
                assert(1 <= vals[3] <= 1e8)
            elif vals[0] == 1:
                assert(len(vals) == 2)
                assert(1 <= vals[1] <= n)
            else:
                assert(False) 