for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10

    for j in range(n):
        m = int(infile.readline())
        if m % 2 == 0:
            outfile.write("{}\n".format(m))