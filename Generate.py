from random import randrange as r

n = 1000000
l = []
for i in range(n):
    x = r(1000) + 1
    l.append(x)

fhand = open('input.txt' , 'w')
fhand.write(' '.join(map(str,l)))
fhand.close()
