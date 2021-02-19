def sgn(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0

for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    l = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    i = 0
    while True:
        m = int(infile.readline())
        if m == 0:
            break
        l[i % 10] = m
        i += 1

    for j in l:
        outfile.write("{}\n".format(j))