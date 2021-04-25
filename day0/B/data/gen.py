#!/usr/bin/env python

# This script should be run in the problem directory
# Requirements:
#   Python >= 3.8.0
#   G++ >= 7.5.0

import subprocess
import random
from os import path

random.seed(0)

# compile std
subprocess.run(["g++", "-O2", "-std=c++14", path.join("namasikanam",
               "std.cpp"), "-o", path.join("namasikanam", "std")])

# the number of testcases
T = 0


def rand_interval():
    l = random.randint(1, n)
    r = random.randint(1, n)
    if l > r:
        l, r = r, l
    return (l, r)


def short_interval():
    l = random.randint(1, n)
    r = random.randint(l, min(l + 10, n))
    return (l, r)


def long_interval():
    l = random.randint(1, min(10000, n))
    r = random.randint(max(n - 10000, l), n)
    return (l, r)


def rand_period(f, interval_generator):
    for i in range(m):
        op = random.randint(0, 1)
        if op == 0:
            l, r = interval_generator()
            x = random.randint(1, 1e8)
            print(op, l, r, x, file=f)
        else:
            i = random.randint(1, n)
            print(op, i, file=f)


def short_period(f, interval_generator):
    assert m > 90000

    # the upperbound of updates (0 means query)
    updates = []
    updates += [100000] * 10
    updates += [10000] * (100 - 10)
    updates += [1000] * (1000 - 100)
    updates += [100] * (10000 - 1000)
    updates += [0] * 10000
    random.shuffle(updates)

    updates += [10] * (m - 20000)

    updates.reverse()

    for i in range(m):
        if updates[i] > 0:
            l, r = interval_generator()
            print(0, l, r, random.randint(1, updates[i]), file=f)
        else:
            print(1, random.randint(l, r), file=f)


def long_period(f, interval_generator):
    assert m > 10000

    for i in range(10000):
        l, r = interval_generator()
        print(0, l, r, random.randint(1, int(1e8)), file=f)

    for i in range(m - 10000):
        op = random.randint(0, 1)
        if op == 0:
            l, r = interval_generator()
            print(op, l, r, random.randint(1, 2), file=f)
        else:
            print(op, random.randint(1, n), file=f)


# testcase 1 as sample
T = T + 1
subprocess.run(["cp", path.join("down", "1.in"), path.join("data", f"{T}.in")])

# testcase 2 for bf to check the correctness of std
T = T + 1
with open(path.join("data", f"{T}.in"), "w") as f:
    print(f"generate {T}.in")
    n = 5000 - random.randint(0, 1)
    m = 5000 - random.randint(0, 1)
    print(n, m, file=f)
    rand_period(f, rand_interval)

# other testcases
for gen_period in [rand_period, short_period, long_period]:
    for interval_generator in [rand_interval, short_interval, long_interval]:
        T = T + 1
        with open(path.join("data", f"{T}.in"), "w") as f:
            print(f"generate {T}.in")
            n = int(1e5) - random.randint(0, 1)
            m = int(1e5) - random.randint(0, 1)
            print(n, m, file=f)
            gen_period(f, interval_generator)

# generate answers
for i in range(1, T + 1):
    with open(path.join("data", f"{i}.in"), "r") as fin:
        with open(path.join("data", f"{i}.ans"), "w") as fans:
            print(f"calculcate the {i}-th testcase")
            subprocess.run([path.join("namasikanam", "std")],
                           stdin=fin, stdout=fans)

# check
cp = subprocess.run(["diff", path.join("data", "1.ans"),
                    path.join("down", "1.ans")])
if cp.returncode != 0:
    print("The answer of the sample is incorrect!")
