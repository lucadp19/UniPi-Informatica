from statistics import mean

for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")

    n = 10
    a = []
    b = [None] * 10
    for _ in range(10):
        m = int(infile.readline())
        a.append(m)
    
    b[0] = a[0]
    outfile.write("{}\n".format(b[0]))
    for i in range(1, 10):
        b[i] = max(a[i], b[i-1])
        outfile.write("{}\n".format(b[i]))
    
    outfile.write("{:.2f}\n".format(mean(b)))