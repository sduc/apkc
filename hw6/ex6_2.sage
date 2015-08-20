#
# Author : Sebastien Duc
#
import sys

def check_business(K):
    profit = 0
    for x in xrange(10000):
        p = 1
        while power_mod(2,p,p) !=2:
            p = getrandbits(K) | 0x1
        if (is_prime(p)):
            profit = profit + 0.01
            print "Your profit is : " + str(profit)
        else:
            profit = profit - 10**6
            print "Your profit is : " + str(profit)
    print "Your profit is : " + str(profit)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Enter an integer")

    K = Integer(sys.argv[1])
    check_business(K)

