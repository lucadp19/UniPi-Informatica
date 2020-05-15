for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = int(infile.readline())
    s = 0
    for j in range(n):
        m = int(infile.readline())
        outfile.write("{}\n".format(abs(m)))