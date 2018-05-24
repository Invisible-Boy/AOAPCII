#! /usr/bin/bash python3
import random

f = open("/Users/invisibleman/MyRepo/temp/test", 'w')

n = random.randint(1, 1000)
f.write(str(n) + '\n')
for x in list(range(1, n)):
    l = []
    k = random.randint(1, 30)
    l.append(str(k))
    base = 2 ** k
    l.append(str(random.randint(1, base)))
    l.append(str(random.randint(1, base)))
    f.write(' '.join(l))
    f.write('\n')
f.close()
