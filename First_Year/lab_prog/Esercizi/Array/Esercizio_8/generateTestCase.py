from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    n = 10
    for j in range(n):
        m = randint(-40, 40)
        myfile.write('{}\n'.format(m))
    k = randint(-20, 25)
    myfile.write("{}\n".format(k))
