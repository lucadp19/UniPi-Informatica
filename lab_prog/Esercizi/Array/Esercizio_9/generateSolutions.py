def sgn(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0

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
    
    l1 = [x for x in l if sgn(x) == sgn(l[-1])]

    for j in l1:
        outfile.write("{}\n".format(j))