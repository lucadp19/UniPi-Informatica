for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    m = int(infile.readline())
    s = 0
    c = 0
    while m != 0:
        c = c + 1
        s = s+m
        m = int(infile.readline())
    outfile.write("{:.2f}\n".format(s/c))