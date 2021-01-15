from triangles import  pascalsTriangleFull
from random import randint

def minzero(r):
    if r < 0:
        return 0
    return r

def xMinusK(pows,k):
    newPows = {}
    powmax = max(pows)
    for i in range(powmax+1):
        if i in pows:
            newPows[i-k] = pows[i]
    return newPows

def sumSet(powSet):
    newPows = {}
    for s in powSet:
        powmax = max(s)
        for i in range(powmax+1):
            if i in s:
                newPows[i] = newPows.get(i,0)+s[i]
    return newPows

def subPowers(powsone, powstwo):
    newPows = {}
    powmax = max(powsone)
    for i in range(powmax):
        if i in powsone:
            if i in powstwo:
                comb = powsone[i] - powstwo[i]
                if comb > 0:
                    newPows[i] = comb
            else:
                newPows[i] = powsone[i]
    return newPows

def getPascalLevel(level,polynom):
    return pascalsTriangleFull(level,polynom)[-1]

def dictPolynPascl(polynoms,pascals):
    zipped = list(zip(polynoms,pascals))
    together = {pn:pc for pn,pc in zipped}
    return together

# Expands a polynomial by pairing the exponent with the coefficient
def expandPolynom(level,minpow,maxpow):
    # gets the polynomial level independent of the range (so 4-6 would be x^2 essentially)
    polynom = maxpow-minpow+1
    # modifier for higher exponents
    mod = minpow*level-1
    # Gets the full set of exponents for variables; the maxpow+3 is to catch the error with lower nums
    fullpows = [i+mod for i in range(1,(polynom-1)*level+2)]
    return fullpows

def polyWithCoeff(level,polynoms,power):
    #print("polys",polynoms)
    #print("pow",power)
    pasclev = getPascalLevel(level,power)
    #print("plev",pasclev)
    together = dictPolynPascl(polynoms,pasclev)
    return together

def nextDict(pows, num, drop, minval):
    #print(pows)
    fullpows = expandPolynom(num, pows[0], pows[-1])
    powsWithCoeffs = polyWithCoeff(num,fullpows,len(pows))
    if len(pows) > 1:
        #print(len(pows)-1)
        #print(num+drop)
        subpows = expandPolynom(num, pows[1], pows[-1])
        powsSub = polyWithCoeff(num, subpows, len(pows)-1)
    else:
        '''print(powsWithCoeffs)
        print({0:0})
        print(powsWithCoeffs)
        print(xMinusK(powsWithCoeffs,minval))'''
        return xMinusK(powsWithCoeffs,minval)
    '''print(powsWithCoeffs)
    print(powsSub)'''
    fixedPows = subPowers(powsWithCoeffs, powsSub)
    # print("fp before",fixedPows)
    #print(fixedPows)
    fixedPows = xMinusK(fixedPows, minval)
    #print(fixedPows,'\n')
    # print("fp",fixedPows,'\n')
    return fixedPows

def probs(num,drop,dietype,minval):
    pows = [i+1 for i in range(0,dietype)] # get basic power set
    allDicts = [] # set up dicts for use with sumSet
    # Loop through the sub power sets
    for i in range(1,len(pows)+1):
        #print(i)
        #print(pows[i:])
        allDicts.append(nextDict(pows[i-1:],num,drop,i))
    #newPows = sumSet(allDicts)
    newPows = {}
    for d in allDicts:
        for e in d:
            newPows[e] = newPows.get(e,0)+d[e]
    #for d in allDicts:
        #print(d)
    #print(newPows)
    prob = ((1/dietype)**num)*newPows[minval]
    return prob


if __name__=="__main__":
    #for i in range(3,19):
    #    print(probs(4,1,6,i))
    #print(probs(4,1,6,3))
    '''for j in range(20):
        good = 0
        bad = 0
        for i in range(100000):
            x = randint(0,20)
            y = randint(0,20)
            if x >= j or y >= j:
                good += 1
            else:
                bad += 1
        print(j+1,":",good/(good+bad))'''
    for i in range(1,21):
        res = 0
        for j in range(i,21):
            res += probs(2,1,20,j)
        print(res)