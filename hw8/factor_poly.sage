#
# Author: Sebastien Duc
#
def is_monic(f):
    return f.coefficients()[-1] == 1

def factor_poly(f):
    return yun_fact(f)

def yun_fact(f):
    f *= f.coefficients()[-1]**(-1)
    out = []
    b = f
    d = f.derivative()
    while not b.is_one():
        a = b.gcd(d)
        assert is_monic(a)
        out.append(a)
        b = b // a
        c = d // a
        d = c - b.derivative()
    return out[1:] 



# tests factor poly on a random poly in F_p^k[X] with a poly of degree n
def test_factor_random(p,k,n):
    Fq.<X> = GF(p**k,name='a')[['X']]
    f = Fq.random_element(n+1).polynomial()
    fact = factor_poly(f)
    print "obtained factorization:" , fact
    
    test_f = f.coefficients()[-1]
    for a,i in zip(fact,range(1,len(fact)+1)):
        assert a.is_squarefree()
        test_f *= a**i
    print test_f , "==" , f
    assert test_f == f

# (d) part of the exercise
# test polynomial given
def test_factor():
    Fq.<X> = GF(5)[['X']]
    f = 3*X^10 + 4*X^7 + 4*X^5 + X^4 + X^3 + 2*X^2 + X + 4
    print "f has factorization" , factor_poly(f.polynomial())

# (d) part of the exercise
# test with sciper generated polynomial
def test_poly_from_sciper(sciper):
    F.<X> = GF(11)[['X']]
    poly = 1
    for i in range(10):
        if i in sciper.digits():
            poly *= (X - i)**i

    print "f (from sciper) has factorization" , factor_poly(poly.polynomial())




