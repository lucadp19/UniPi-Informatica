for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")
    n = int(infile.readline())
    while n != 1:
        outfile.write("{}\n".format(n))
        if n % 2 == 0:
            n = n//2
        else:
            n = 3*n + 1
    
    outfile.write("1\n")