#!/usr/bin/env python

# This script should be run in the directory of namasikanam
# Requirements:
#   Python >= 3.8.0
#   G++ >= 7.5.0

import subprocess
import random
from os import path
from tqdm import tqdm

random.seed(0)

# compile std
# subprocess.run(["g++", "-O2", "-std=c++14", path.join("namasikanam",
#                "std.cpp"), "-o", path.join("namasikanam", "std")])


def rand_interval():
    l = random.randint(1, n)
    r = random.randint(1, n)
    if l > r:
        l, r = r, l
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


corr = True
pbar = tqdm(total=100000)
while corr:
    pbar.update()

    with open(path.join("stress.in"), "w") as f:
        n = 20
        m = 1000
        print(n, m, file=f)
        rand_period(f, rand_interval)
        # print('[generated] stress')

    with open('stress.in', 'r') as infile:
        with open('stress.ans', 'w') as ansfile:
            subprocess.run(['./std'],
                           stdin=infile,
                           stdout=ansfile)
        # print('[runned] std')

    with open('stress.in', 'r') as infile:
        with open('stress.out', 'w') as outfile:
            subprocess.run(['./bf'],
                           stdin=infile,
                           stdout=outfile)
        # print('[ruuned] bf')

    corr = subprocess.run(['diff', 'stress.ans', 'stress.out'],
                          stdout=subprocess.DEVNULL).returncode == 0
