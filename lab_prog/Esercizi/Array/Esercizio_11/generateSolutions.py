for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10
    a = []
    b = []
    for j in range(5):
        m = int(infile.readline())
        a.append(m)
    for j in range(5):
        m = int(infile.readline())
        b.append(m)
    
    for i in range(5):
        ok = True
        for j in range(5):
            if a[i] >= b[j]:
                ok = False
                break
        if ok == True:
            outfile.write("{}\n".format(i))
            break
    
    if ok == False:
        outfile.write("-1\n")