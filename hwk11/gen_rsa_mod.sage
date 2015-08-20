#
# Author: Sebastien Duc
#

B = 120
P_SIZE = 512
N_SIZE = 2 * P_SIZE

# Main function for question 11.1.1
def gen_rand_rsa_1():
    while True:
        a = random_prime( 2**(B) , lbound = 2**(B - 1) )
        b = random_prime( 2**(B) , lbound = 2**(B - 1) )

        p = 1 + a * floor(2**(P_SIZE - bit_size(a)))
        q = 1 + b * floor(2**(P_SIZE - bit_size(b) + 1))
        n = p*q
        p_is_prime = is_prime(p)
        q_is_prime = is_prime(q)
        retry = False
        while not has_correct_size(n,N_SIZE) or not p_is_prime or not q_is_prime:
            if not p_is_prime:
                p += a
                p_is_prime = is_prime(p)
                n += p*a
            if not q_is_prime:
                q -= b
                q_is_prime = is_prime(q)
                n -= p*b
            if q_is_prime and p_is_prime and bit_size(n) < N_SIZE:
                p += a
                q -= b
                n = p*q
            if bit_size(n) > N_SIZE:
                retry = True
                break

        if not retry:
            return n

# Main function for question 11.1.2
def gen_rsa_moduli_2():
    p = gen_strong_prime()
    q = gen_strong_prime()

    n = p*q
    assert bit_size(n) == N_SIZE
    return n

# for question 11.1.2
def gen_strong_prime():
    p_1 = random_prime( 2**(B) , lbound = 2**(B - 1) )
    p_2 = random_prime( 2**(B) , lbound = 2**(B - 1) )

    # we apply the CRT
    R = p_2.inverse_mod(p_1) * p_2 - p_1.inverse_mod(p_2) * p_1

    start = randint( ceil(sqrt(2) * 2^511) , 2^512 - 1) 

    p = start + (R - start).mod(p_1 * p_2)
    while (not is_prime(p)):
        p += p_1 * p_2

    assert p_1.divides(p-1) and p_2.divides(p+1)

    return p

def gen_rsa_moduli_4():
    p = gen_super_strong_prime()
    q = gen_super_strong_prime()

    n = p*q
    assert bit_size(n) == N_SIZE
    return n


def gen_super_strong_prime():
    p_1 = random_prime( 2**(B) , lbound = 2**(B - 1) )
    p_2 = random_prime( 2**(B) , lbound = 2**(B - 1) )
    p_3 = 5
    while (p_3 % 4 != 3 or legendre_symbol(-3,p_3) == -1):
        p_3 = random_prime( 2**(B) , lbound = 2**(B - 1) )
    p_4 = 0
    while p_4 % 4 != 1: # wait until -1 is a QR
        p_4 = random_prime( 2**(B) , lbound = 2**(B - 1) )


    # we apply the CRT
    a,b = 1,-1
    sqrt_delta = power_mod(-3,(p_3+1)//4,p_3)
    c = Integer(Mod((-1 + sqrt_delta)/2,p_3))
    d = Integer(sqrt(Mod(-1,p_4)))

    pp_1 = p_2*p_3*p_4
    pp_2 = p_1*p_3*p_4
    pp_3 = p_1*p_2*p_4
    pp_4 = p_1*p_2*p_3

    R = a * pp_1 * pp_1.inverse_mod(p_1) + b * pp_2 * pp_2.inverse_mod(p_2) + \
            c * pp_3 * pp_3.inverse_mod(p_3) + d * pp_4 * pp_4.inverse_mod(p_4)

    start = randint( ceil(sqrt(2) * 2^511) , 2^512 - 1) 
    p1_p2_p3_p4 = pp_1 * p_1 
    p = start + (R - start).mod(p1_p2_p3_p4)
    while (not is_prime(p)):
        p += p1_p2_p3_p4

    assert p_1.divides(p-1) and p_2.divides(p+1) \
            and p_3.divides(p^2 + p + 1) and p_4.divides(p^2 + 1),"\n"+\
            "p-1 :         " + str(p_1.divides(p-1)) + "\n"+\
            "p+1 :         " + str(p_2.divides(p+1)) + "\n"+\
            "p^2 + p + 1 : " + str(p_3.divides(p^2+p+1)) + "\n" +\
            "p^2 + 1 :     " + str(p_4.divides(p^2 + 1)) + "\n"

    return p

def has_correct_size(p, size):
    return bit_size(p) == size

def bit_size(n):
    return len(bin(n)) - 2 


def test_gen_rand_rsa():
    for i in range(100):
        gen_rand_rsa()
