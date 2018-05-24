f = open('/Users/invisibleman/MyRepo/temp/test', 'w')
import random
m = 20
while(m > 0):
    n = random.randint(10, 20)
    f.write(str(n) + '\n')
    while(n > 0):
        t = random.randint(1, 50)
        f.write(str(t) + ' ')
        n = n - 1
    f.write('\n')
    m = m - 1
f.write('0')
f.close()
