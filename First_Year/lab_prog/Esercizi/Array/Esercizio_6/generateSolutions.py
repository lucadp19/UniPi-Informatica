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

    for j in range(n):
        if l[j] > 0 and l[j] % 2 == 0:
            outfile.write("{}\n".format(l[j]))
        elif j < n-1 and l[j] < 0 and l[j+1] > 0:
            outfile.write("{}\n".format(l[j]))
