from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    n = 12
    for _ in range(n):
        m = randint(-10, 15)
        myfile.write('{}\n'.format(m))
