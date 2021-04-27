from os import system
from random import randint
from time import time

def run(s):
	t=time()
	print(s)
	if system(s): exit(1)
	print(time()-t,'s')

def gen(fn):
	with open(fn,'w') as f:
		n = randint(1,1000)
		m = randint(1,1000)
		n = 100000
		m = 500000
		f.write(f'{n}\n')
		a = [randint(1,10) for i in range(n)]
		f.write(' '.join(map(str,a)))
		f.write(f'\n{m}\n')
		for i in range(m):
			l = randint(1,n)
			r = randint(1,n)
			if l>r: l,r = r,l
			l2 = randint(1,n-(r-l))
			f.write(f'{l} {r} {l2}\n')

for T in range(10000):
	print(f'--{T}--')
	gen('1.in')
	run('./std < 1.in > o1.txt')
	run('./bf < 1.in > o2.txt')
	run('diff o1.txt o2.txt')
