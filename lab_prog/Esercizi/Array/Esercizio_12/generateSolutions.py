def max(a):
    m, i_max = a[0], 0
    for i in range(len(a)):
        if a[i] > m:
            m = a[i]
            i_max = i
    return (m, i_max)

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
    
    m, i_m = max(l)
    outfile.write("{} {}\n".format(i_m, m))