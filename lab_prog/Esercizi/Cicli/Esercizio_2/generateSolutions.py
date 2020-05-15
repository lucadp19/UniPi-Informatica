for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = int(infile.readline())

    for j in range(n):
        m = int(infile.readline())
        if m > 0:
            outfile.write("positivo\n")
        elif m < 0:
            outfile.write("negativo\n")
        else:
            outfile.write("0\n")