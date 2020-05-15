for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = int(infile.readline())
    c = 0
    for j in range(n):
        m = int(infile.readline())
        if m % 4 == 0:
            c = c+1
    outfile.write("{}\n".format(c))