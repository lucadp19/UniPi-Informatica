def mcd(a, b):
    while b>0:
        r=a%b
        a,b=b,r
    return a

for i in range(6):
    infilename = "input" + str(i) + ".txt"
    outfilename = "output" + str(i) + ".txt"
    infile = open(infilename, "r")
    outfile = open(outfilename, "w")
    n, m = map(int, infile.readline().split())
    d = mcd(n ,m)
    
    outfile.write("{}\n".format(d))