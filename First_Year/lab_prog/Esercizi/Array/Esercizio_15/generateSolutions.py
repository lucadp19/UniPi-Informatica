for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10
    a = []
    b = []
    c = [None] * 3
    for j in range(6):
        m = int(infile.readline())
        a.append(m)
    for j in range(6):
        m = int(infile.readline())
        b.append(m)
    
    j = 0
    while 2*j < len(a) and 2*j + 1 < len(b):
        c[j] = a[2*j] * b[2*j + 1]
        j += 1
    
    outfile.write("{}\n".format(min(c))) 