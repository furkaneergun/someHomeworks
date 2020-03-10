import random
import sys
from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy.ecdsa      import ECDSA
from ecpy import ecrand
from Crypto.Hash import SHA3_256
def KeyGen(E):
    n = E.order
    P = E.generator
    # Payer
    payer_sk = random.randint(2,n-1)
    payer_pk = payer_sk*P
    return payer_sk, payer_pk

def do_sign(msg, pv_key, k, curve): 
    n = curve.order
    G = curve.generator
    k = k%n
    msg = int.from_bytes(SHA3_256.new(msg).digest(), 'big')
    Q = G*k
    kinv = pow(k,n-2,n)
    r = Q.x % n
    if r == 0:
        return None

    s = (kinv*(msg+pv_key*r)) %n
    s= ((pv_key*r)-(k*msg))%n
    if s == 0:
        return None    
    return s, r

def SignGen(message, E, sA):
    order = E.order
    for i in range(1,10):
        k = ecrand.rnd(order)
        s, r = do_sign(message, sA,k, E)
        if(s and r):
            return s, r
def SignVer(message, s, r, E, QA):
    curve = QA.curve
    n     = curve.order
    G     = curve.generator
    if (r == None or
        r > n     or
        s > n     ) :
        return False

    h = int.from_bytes(SHA3_256.new(message).digest(),'big')

    c   = pow(h, n-2, n)
    u1  = (s*c)%n
    u2  = (r*c)%n
    u1G = (n-u1)
    if type(QA)==Point:
        QA=ECPublicKey(QA)
    u2Q = u2*QA.W
    V=u1G*G+u2Q
    x=V.x%n
    
    return not (x == r)


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




