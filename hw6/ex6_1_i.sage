#
# Author: Sebastien Duc
#
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Enter a sciper number")

    s = Integer(sys.argv[1])

    L = power(2,1024)*s
    U = L + power(2,20)

    primes = []
    p = pari("nextprime("+str(L)+")")
    primes.append(p)
    p = p + 1
    while p < U:
        p = pari("nextprime("+str(p)+")")
        primes.append(p)
        p = p + 1

    print "You have generated " + str(len(primes)) + " primes"

