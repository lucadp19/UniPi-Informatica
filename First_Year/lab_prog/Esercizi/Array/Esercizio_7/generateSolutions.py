for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10
    l = []
    for j in range(n):
        m = int(infile.readline())
        l.append(m)
    to_find = int(infile.readline())

    if to_find in l:
        outfile.write("1\n")
    else:
        outfile.write("0\n")
