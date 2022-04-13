def gcd(n, m):
    """ greatest common divisor """

    bigg = max(n,m)
    smol = min(n,m)

    if bigg == 0:
        return smol
    
    if smol == 0:
        return bigg

    bigg -= smol

    out = gcd(bigg, smol)

    return out


def factorial(n):
    """ factorial function """
    if n <= 1:
        return n
    
    out = n * factorial(n-1)

    return out

    
def gauss(n):
    """ Gaussian sum """
    if n <= 1:
        return n
    
    out = n + gauss(n-1)

    return out

def gauss2(n):

    out = 0
    for i in range(0, n+1):
        out += i 
    
    return out
    
def is_square(n):
    """ isSquare function """
    
    i = n**0.5

    return i == int(i)

print(gcd(81, 18))
print(factorial(10))
print(gauss2(10))
print(is_square(18))