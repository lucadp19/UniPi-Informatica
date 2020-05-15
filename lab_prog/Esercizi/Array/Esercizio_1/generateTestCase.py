from random import randint

for i in range(6):
    filename = "input" + str(i) + ".txt"
    myfile = open(filename, "w")
    outfilename = "output" + str(i) + ".txt"
    outfile = open(outfilename, "w")
    for j in range(10):
        m = randint(0, 100)
        myfile.write('{}\n'.format(m))
        outfile.write('{}\n'.format(m))
