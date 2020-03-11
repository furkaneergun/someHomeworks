from Crypto.Hash import SHA3_256
import random

def recCallMerkle(hashList):
    currVal=len(hashList)
    if(currVal==1):
        return hashList[0]
    else:
        subTree=[]
        for i in range(currVal-1):
            if(i%2==0):
                subTree.append(SHA3_256.new(hashList[i]+hashList[i+1]).digest())
        return recCallMerkle(subTree)

def CheckPow(PoWLen, allLines):
    allBlocks=[]
    for i in range(len(allLines)-9):
        if(i%9 == 0):
            allBlocks.append(''.join(allLines[i:i+9]))
    prevPow=allLines[-2][14:].rstrip()
    hashedList=[SHA3_256.new(i.encode("utf-8")).digest() for i in allBlocks]
    nonceValue=int(allLines[-1][7:].rstrip())
    rootValue=recCallMerkle(hashedList)
    tobedigest=rootValue+prevPow.encode("utf-8")+nonceValue.to_bytes((nonceValue.bit_length()+7)//8, byteorder='big')
    PoW=SHA3_256.new(tobedigest).hexdigest()
    return PoW

    
def PoW(PoWLen, allLines):
    allBlocks=[]
    for i in range(len(allLines)-9):
        if(i%9 == 0):
            allBlocks.append(''.join(allLines[i:i+9]))
    prevPow=allLines[-1][14:].rstrip()
    hashedList=[SHA3_256.new(i.encode("utf-8")).digest() for i in allBlocks]
    rootValue=recCallMerkle(hashedList)
    output=''.join(allLines)
    search=True
    while search:
        nonceValue=random.randint(2**16,2**64)
        tobedigest=rootValue+prevPow.encode("utf-8")+nonceValue.to_bytes((nonceValue.bit_length()+7)//8, byteorder='big')
        x=SHA3_256.new(tobedigest).hexdigest()
        if(x[:PoWLen]==(PoWLen*"0")):
            search=False
            return "Nonce: "+str(nonceValue)+"\n"

def AddBlock2Chain(PoWLen, TxCnt, block_candidate, PrevBlock):
    prevpow="00000000000000000000\n"
    if PrevBlock=="":
        block_candidate.append("Previous PoW: "+"00000000000000000000\n")
    else:
        prevpow=CheckPow(PoWLen, PrevBlock)
        block_candidate.append("Previous PoW: "+CheckPow(PoWLen, PrevBlock)+"\n")
    nonce=PoW(PoWLen, block_candidate)
    block_candidate.append(nonce)
    return ''.join(block_candidate), prevpow