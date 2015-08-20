# the actual implementation of the multiply modula n using the algorithm
# described in the PDF.
# It takes 5 integers as input and returns an integer.
def multiply_mod(a, b, n, l, k):
    """ This one code is implemented using schoolbook multiplication but
    commented since not efficient

    a_list = l_bit_int2list(a,l)
    b_list = l_bit_int2list(b,l)
    n_list = l_bit_int2list(n,l)

    p = multiply(a_list,b_list,l)
    
    p_left , p_right = p[:len(p) - 2*k] , p[len(p) - 2*k:]
    n__times__p_left = multiply(p_left,n_list,l) 
    
    p = substract(p, n__times__p_left, l)
    if l_bit_list2int(p,l) >= 0:
        return l_bit_list2int(p,l)
    p_left , p_right = p[:len(p) - 2*k] , p[len(p) - 2*k:]
    n__times__p_left = l_bit_int2list(l_bit_list2int(p_left,l)*n,l)
    p = substract(p, n__times__p_left, l)
    if l_bit_list2int(p,l) < 0:
        return l_bit_list2int(p,l) + n
    return l_bit_list2int(p,l)
    """
    # this code is more efficient and sufficient as a proof of concept
    # it's been used because I tested my code on random inputs multiple times to
    # check the validity.

    p = a*b
    
    p_list = l_bit_int2list(p,l)
    p_left = l_bit_list2int(p_list[:len(p_list) - 2*k],l) 
    p_right = l_bit_list2int(p_list[len(p_list) - 2*k:],l)
    np_left = p_left*n
    
    p = p - np_left
    if (p >= 0 ):
        return p
    
    p_list = l_bit_int2list(p,l)
    p_left = l_bit_list2int(p_list[:len(p_list) - 2*k],l) 
    p_right = l_bit_list2int(p_list[len(p_list) - 2*k:],l)

    np_left = p_left*n
    p = p - np_left
    if (p < 0):
        p = p + n
    return p


####
#

# function used to test the multiplication running it on random inputs
def test():
    for x in xrange(10000):
        l,k = Integer(randint(1,500)),Integer(randint(1,500))
        a,b,n = gen_rand_input(l,k)
        assert(a*b%n == multiply_mod(a,b,n,l,k))

# used to generate random inputs a,b,n given l and k
def gen_rand_input(l,k):
    t = Integer(randint(1,2**(l*k)-1))
    n = 2**(2*k*l) + t
    a = Integer(randint(0,n-1))
    b = Integer(randint(0,n-1))
    return a,b,n

def l_bit_int2list(a_int, l):
    ret = a_int.digits(2**l)
    ret.reverse()
    return ret

def l_bit_list2int(a_list, l):
    return sum([a*2**(i*l) for (a,i) in zip(a_list,range(len(a_list))[::-1])])

######################################################
# Some functions to do multiplication without modulo #
######################################################

def substract(a,b,l):
    return l_bit_int2list(l_bit_list2int(a,l) - l_bit_list2int(b,l),l)

# multiplier  of two integers a,b represented as list where each component is
# a digit in base 2^l
def multiply(a,b,l):
    if len(a) == 1:
        return multiply_part(a[0],b,l)
    return summation(multiply(a[:-1],b,l) + [0] , multiply_part(a[-1],b,l) , l)

# subroutine used by multiply:
# multiply a single digit a_i with integer b (list) in base 2^l
def multiply_part(a_i, b, l, c=0):
    a_i__times__b = l_bit_multiply(a_i, b[-1], c, l)
    if len(b) == 1:
        return a_i__times__b
    return multiply_part(a_i, b[:-1], l, c=a_i__times__b[0]) + [a_i__times__b[1]]

# multiply two l bit integers and return a 2l bit result in a list where each
# element is l bit representation
def l_bit_multiply(a_i, b_i, carry, l):
    prod = a_i * b_i + carry
    return [prod >> l, prod & (2**l - 1)]

# adder for two integer a,b represented as list where each component is a digit
# in base 2^l
def summation(a,b,l,c=0):
    if len(a) == 0 and len(b) == 0:
        return [c] if c == 1 else []
    if a == [] and len(b) > 0:
        a = [0]
    if b == [] and len(a) > 0:
        b = [0]
    a_i__plus__b_i = l_bit_add(a[-1], b[-1], c, l)
    return summation(a[:-1], b[:-1], l, c=a_i__plus__b_i[0]) + [a_i__plus__b_i[1]]

def l_bit_add(a_i, b_i, carry, l):
    ret = a_i + b_i + carry
    return l_bit_splitter(ret,l)


def l_bit_splitter(a,l):
    return [a >> l, a & (2**l -1)]
