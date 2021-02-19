for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    m = int(infile.readline())
    c = 0
    while m != 0:
        c = c+1
        m = int(infile.readline())
    outfile.write("{}\n".format(c))