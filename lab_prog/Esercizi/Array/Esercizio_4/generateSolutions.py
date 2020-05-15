for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")
    n =10
    c = 0
    s = 0
    for j in range(n):
        m = int(infile.readline())
        if m > 0:
            c = c+1
            s = s+m
    outfile.write("{:.2f}\n".format(s/c))