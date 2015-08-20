#
# Author: Sebastien Duc
#

# generate q,p s.t. q | p^k - 1 and q not| p^s - 1 
# for all s | k
def ex10_3_2((L,B),k):
    # check inputs
    if k not in range(1,8) or \
       (L,B) not in [(160,1024),(212,2048)]:
        print("Values are not in the correct range")
        return

    # the actual algorithm #
    ########################
    f = cyclotomic_polynomial(k)

    r = None
    if k in [1,2]:
        r = 2**(L-1)
    elif k in [3,4,6]:
        r = floor(2**((L-1)/2))
    elif k == 5:
        r = floor(2**((L-1)/4))
    elif k == 7 and L == 160:
        r = floor(2**((L-1)/6))
    elif k == 7:
        r = floor(2**((L-1)/6))

    while True:
        q = f(x=r)
        #print "q is prime", len(bin(q)) - 2, is_prime(q)
        if is_prime(q) and correctSize(q,L):
            a = floor((2**((B-1)/k)-r)/q)
            p = r + a*q

            found = False
            pk = 0
            
            while not found:
                p += q
                if is_prime(p):
                    pk = p**k
                    if tooLarge(pk,B,k==7 and L == 160):
                        break
                    print "bit-size(q)" , len(bin(q)) - 2
                    print "bit-size(p^k)", len(bin(pk)) - 2
                    found = correctSize(pk,B) if k != 7 or L != 160 else True

            if found:
                if k == 1:
                    return (q,pk,find_generator(q,pk))
                else:
                    return (q,pk)

        if k==1:
            r = next_prime(r) + 1
        elif k == 7 and L == 160:
            r += 1
        else:
            r += 1

def correctSize(p,B):
    return len(bin(p))-2 == B

def tooLarge(p,B,nasty):
    return len(bin(p)) - 2 > B if not nasty else false

def find_generator(q,p):
    while True:
        h = randint(1,p-1)
        g = power_mod( h, (p-1)//q , p )
        if g != 1:
            return g


def test_function():
    test_LB(160,1024)
    test_LB(212,2048)

        
def test_LB(L,B):
    print "Test for (L,B) = ("+str(L)+","+str(B)+")"
    print "---------------------------"
    print "-> test k = 1"
    k = 1
    q,p,g = ex10_3_2((L,B),k)
    assert is_prime(q) and is_prime(p)

    for k in range(2,8):
        print "-> test k =" , k
        q,pk = ex10_3_2((L,B),k)
        check_case(q,pk,k)

def check_case(q,pk,k):
    assert is_prime(q) and is_prime_power(pk)
    p = pk.nth_root(k)
    assert is_prime(p)
    for s in divisors(k):
        assert p^s - 1 % q != 0
