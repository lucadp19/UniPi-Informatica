from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    a, b = randint(5+i*2, 5 + i*9), randint(5+i*2, 5 + i*9)
    myfile.write('{} {}\n'.format(a, b))
    # for j in range(n):
    #     m = randint(1, 20)
    #     myfile.write('{}\n'.format(m))
    # myfile.write('0\n')