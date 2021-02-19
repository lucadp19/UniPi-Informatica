from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    n = 10
    for j in range(n):
        m = randint(0, 20)
        myfile.write('{}\n'.format(m))