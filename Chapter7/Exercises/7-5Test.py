f = open("/Users/invisibleman/MyRepo/temp/input", "w")
import random
m = 1000
while m > 0:
    m = m - 1
    n = random.randint(1, 20)
    f.write(str(n) + '\n')
    l = 5
    while l > 0:
        l = l - 1
        nn = n
        while nn > 0:
            nn = nn - 1
            t = random.randint(0, 10)
            if t < 4:
                f.write('X')
            else:
                f.write('.')
        f.write('\n')
f.write(str(0) + '\n')

