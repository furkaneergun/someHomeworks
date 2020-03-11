#!/usr/bin/env python
# coding: utf-8

# In[4]:

import string
import random
import pyprimes
import warnings
from Crypto.Hash import SHA3_256
from Crypto.Hash import SHAKE128


def egcd(a, b):
    x, y, u, v = 0, 1, 1, 0
    while a != 0:
        q, r = b // a, b % a
        m, n = x - u * q, y - v * q
        b, a, x, y, u, v = a, r, u, v, m, n
    gcd = b
    return gcd, x, y


def modinv(a, m):
    if a < 0:
        a = a + m
    gcd, x, y = egcd(a, m)
    if gcd != 1:
        return None  # modular inverse does not exist
    else:
        return x % m


def random_prime(bitsize):
    warnings.simplefilter('ignore')
    chck = False
    while chck == False:
        p = random.randrange(2 ** (bitsize - 1), 2 ** bitsize - 1)
        chck = pyprimes.isprime(p)
    warnings.simplefilter('default')
    return p


def large_DL_Prime(q, bitsize):
    warnings.simplefilter('ignore')
    chck = False
    while chck == False:
        k = random.randrange(2 ** (bitsize - 1), 2 ** bitsize - 1)
        p = k * q + 1
        chck = pyprimes.isprime(p)
    warnings.simplefilter('default')
    return p


def Param_Generator(qsize, psize):
    q = random_prime(qsize)
    p = large_DL_Prime(q, psize - qsize)
    tmp = (p - 1) // q
    g = 1
    while g == 1:
        alpha = random.randrange(1, p)
        g = pow(alpha, tmp, p)
    return q, p, g


# Generating private-public key pair
def Key_Gen(q, p, g):
    s = random.randint(1, q)  # private key
    h = pow(g, s, p)  # public key
    return s, h


# Signature generation
def Sig_Gen(message, a, k, q, p, g):
    shake = SHAKE128.new(message)
    h = int.from_bytes(shake.read(q.bit_length() // 8), byteorder='big')
    r = pow(g, k, p) % q
    s = (modinv(k, q) * (h + a * r)) % q
    return r, s


# Signature verification
def Sig_Ver(message, r, s, beta, q, p, g):
    shake = SHAKE128.new(message)
    h = int.from_bytes(shake.read(q.bit_length() // 8), byteorder='big')
    u1 = (modinv(s, q) * h) % q
    u2 = (modinv(s, q) * r) % q
    v1 = (pow(g, u1, p) * pow(beta, u2, p) % p) % q
    if v1 == r:
        return True
    else:
        return False


# In[25]:


def GenerateOrRead(txtName):
    try:
        f = open(txtName, "r")
        lines=f.readlines()
        q=lines[0].strip()
        p=lines[1].strip()
        g=lines[2].strip()
    except IOError:
        q, p, g = Param_Generator(224, 2048)
        while(p.bit_length()!=2048):
            q, p, g = Param_Generator(224, 2048)
    finally:
        f.close()
        return int(q), int(p), int(g)
    
def random_string(X):
	return ''.join(random.choice(string.ascii_lowercase) for x in range(X))
	
	
def KeyGen(q, p, g):
    alpha = random.randint(1, q)  # private key
    beta = pow(g, alpha, p)  # public key
    return alpha, beta

def SignGen(message, q, p, g, alpha):
    h=int.from_bytes(SHA3_256.new(message).digest(), byteorder="big")
    h=h%q
    k=random.randint(1, q-2)
    r=pow(g, k, p)%q
    s=(alpha*r)-(k*h)
    return s,r


def SignVer(message, s, r, q, p, g, beta):
    h=int.from_bytes(SHA3_256.new(message).digest(), byteorder="big")
    h=h%q
    v=modinv(h, q)
    z1=(s*v)%q
    z2=(r*v)%q
    u=(pow(modinv(g,p),z1,p)*pow(beta, z2, p))%q
    return u==r


# In[ ]:





# In[ ]:





# In[ ]:




