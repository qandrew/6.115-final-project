
a= [1,10,3,4,4,4,10]
c = enumerate(a)

print [i for i, j in enumerate(a) if j == max(a)]