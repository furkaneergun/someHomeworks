#!/usr/bin/env python
# coding: utf-8

# In[3]:


import random
import pyprimes
import warnings
from Crypto.Hash import SHA3_256
from Crypto.Hash import SHAKE128
import math

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

def SignGen(message, q, p, g, alpha):
    h=int.from_bytes(SHA3_256.new(message.encode("utf-8")).digest(), byteorder="big")
    h=h%q
    k=random.randint(1, q-2)
    r=pow(g, k, p)%q
    s=(alpha*r)-(k*h)
    return s,r


# In[20]:


def gen_random_tx(q, p, g):
    output=""
    SerialNumber=random.getrandbits(128)
    while(SerialNumber.bit_length()!=128):
        SerialNumber=random.getrandbits(128)
    alpha, beta=Key_Gen(q,p,g)
    payer_public=beta
    payee_public=random.getrandbits(beta.bit_length())
    while(payee_public.bit_length()!=payer_public.bit_length()):
        payee_public=random.getrandbits(beta.bit_length())
    amount=random.randint(1, 1000000)
    output+="*** Bitcoin transaction ***\n"
    output+="Serial number: "
    output=output+str(SerialNumber)+"\n"
    output=output+"Payer public key (beta): "+str(payer_public)+"\n"
    output=output+"Payee public key (beta): "+str(payee_public)+"\n"
    output=output+"Amount: "+str(amount)+"\n"
    s, r=SignGen(output, q, p, g, alpha)
    output=output+"Signature (s): "+str(s)+"\n"
    output=output+"Signature (r): "+str(r)+"\n"
    return output
    
def gen_random_txblock(q, p, g, TxCnt, filename):
    if math.log(TxCnt, 2).is_integer():
        f = open(filename, "w")
        for i in range(TxCnt):
            output=gen_random_tx(q,p,g)
            f.write(output)


# In[4]:





# In[ ]:





# In[ ]:




