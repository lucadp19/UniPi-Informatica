for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = int(infile.readline())

    for j in range(n):
        a, b = map(int, infile.readline().split())
        if a > b:
            outfile.write("maggiore\n")
        elif a < b:
            outfile.write("minore\n")
        else:
            outfile.write("uguale\n")