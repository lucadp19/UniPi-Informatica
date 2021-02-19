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
    k = int(infile.readline())
    
    for elem in l:
        if elem > k:
            outfile.write("{}\n".format(elem))
