import random
f=open('100M','w')
for i in range(100000000):
    f.write(str(random.randint(0,10000))+" ")
