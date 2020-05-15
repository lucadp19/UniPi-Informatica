from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    n = randint(5, 5 + 5 * i)
    # myfile.write('{}\n'.format(n))
    for j in range(n):
        m = randint(1, 100)
        myfile.write('{}\n'.format(m))
    myfile.write('0\n')
