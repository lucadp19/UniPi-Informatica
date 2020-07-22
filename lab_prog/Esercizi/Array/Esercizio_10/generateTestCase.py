from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    n = randint(10, 10+(i+1)*3)
    for j in range(n):
        while True:
            m = randint(-40, 40)
            if m != 0:
                break
        myfile.write('{}\n'.format(m))
    myfile.write("0\n")
