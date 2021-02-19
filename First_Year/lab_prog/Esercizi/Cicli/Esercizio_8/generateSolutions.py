for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    m = int(infile.readline())
    s = 0
    while m != 0:
        s = s+m
        m = int(infile.readline())
    outfile.write("{}\n".format(s))