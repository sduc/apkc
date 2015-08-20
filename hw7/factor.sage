#
# Author: Sebastien Duc
#


def random1_n(n):
    return Integer(randint(0,n-1)) 

def my_factor(n):
    already_found = [random1_n(n)]
    cI, cII = 1,0
    while True:
        same = False
        k = random1_n(n)
        cI += 1 
        for x in already_found:
            # just check if we haven't already picked this number
            if x == k:
                same = True
                print "Duplicate"
                break
            
            d = gcd(x-k,n)
            cII += 1
            if d > 1:
                print "We did " + str(cI) + " calls to black box I"
                print "We did " + str(cII) + " calls to black box II"
                return (d,n/d)

        if not same:
            already_found.append(k)


def test_bit(K):
    p = random_prime(2**K,2**(K+1))
    q = random_prime(2**K,2**(K+1))
    print "p = " + str(p) + ", q = " + str(q)
    r = my_factor(p*q)
    print "We found p = " + str(r[0]) + ", and q = " + str(r[1]) 
