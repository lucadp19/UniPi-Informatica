for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10
    a = []
    b = []
    c = [None] * 10
    for j in range(5):
        m = int(infile.readline())
        a.append(m)
    for j in range(5):
        m = int(infile.readline())
        b.append(m)
    
    for i in range(5):
        c[i] = max(a[i], b[i])
        outfile.write("{}\n".format(c[i]))