######################
# APKC - HW 2        #
# Sebastien Duc      #
######################

def extend2rsa(k):
    K = 0 if k==0 else len(str(k))
    # generate a prime of K digits
    while True:
        p = random_prime(pow(10,K)-1,lbound=pow(10,K-1))
        n,q = sub_routine(k,K,p)
        if (floor(n/pow(10,K)) == k):
            return (n,p,q)


def gen_rsa_rev_prime(K):
    while True:
        p = random_prime(pow(10,K)-1,lbound=pow(10,K-1))
        rev_p = int(str(p)[::-1])
        n,q = sub_routine(rev_p,K,p)
        if (floor(n/pow(10,K)) == rev_p):
            return (n,p,q)

def sub_routine(k,K,p):
    n_tmp = k*pow(10,K)
    # upper rouond it to the nearest multiple of p
    q = ceil(n_tmp/p)
    n_tmp = ceil(n_tmp/p)*p
    q = next_prime(q)
    n = p*q
    return (n,q)
