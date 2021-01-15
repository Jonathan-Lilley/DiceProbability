'''                                     TRIANGLES!!!                                        '''

'''

        AIGHT SO
        Pascals Triangle is a really useful mathematical concept that allows you to expand 
        binomials ((x+x^2)^2 to x^2+2x^3+x^4, etc) without having to do all the shitty work
        
        BUT
        
        mr pascal was a dickwad and only gave us an equation for binomials
        
        THANKFULLY
        IM A SMART PERSON AND I DESIGNED AN ALGORITHM TO DETERMINE FOR AAAAAAAAAALL POLYNOMIALS
        TRINOMIALS, QUADRINOMIALS, YOU NAME IT WE GOT IT
        
        ... anyway, its a nice little calculation that allows us to generate n-level polynomial ((polynomial)^n)
        expansions without doing all the dirtywork
        
        so, to explain:
        
        To calculate a pascal's triangle, you start with 1 at the top, then the second level is 1 ... n ... 1
        where n is the highest power in the polynomial. Once you've done that, each subsequent layer is determined by
        the previous layer -- by adding the numbers in the previous layer.
        The first number in each layer is 1, and each subsequent number is the sum of the numbers above it, based on the
        polynomial exponent (e.g. for a trinomial each number is the sum of the three numbers above it, for a
        quadrinomial its four, etc.). The one catch is that the first p-numbers, where p is the polynomial power, have 
        to be calculated with the numbers above them with... Well, it's easier if you see it and figure it out, i can't
        explain well.
        
        Here are two pascal's triangles:
        
               1                              1
             1 2 1                        1 2 3 2 1
            1 3 3 1                     1 3 6 7 6 3 1
           1 4 6 4 1                1 4 10 16 19 16 10 4 1
         1 5 10 10 5 1           1 5 15 30 45 51 45 30 15 5 1
        1 6 15 20 15 6 1     1 6 21 50 90 126 141 126 90 50 21 6 1

        If you wanna check my math go ahead but i'm pretty sure i got it. 

'''

# Makes the minimum number 0
# This is used to catch the first numbers in a line so they dont get to negative initial counts
def minzero(r):
    if r < 0:
        return 0
    return r

# Calculates a triangle for any type of univariate polynomial expansion
# given the polynomial type and the expansion level
# Math explanation above
# fuck all of this lmao
def pascalsTriangleFull(level,polynom):
    # initialize triangle 2d array
    triangle = [[1 for i in range(polynom)]]
    # Start loop to generate levels
    for i in range(level-1):
        # gets the current level to generate from
        cur = triangle[i]
        # initializes a level as 1s
        a = [1 for j in range(len(cur)+(polynom-1))]
        # gets the initial numbers of the level
        # calculates the rest
        for j in range(1,len(a)-1):
            # minzero to catch the first few numbers where the index would go below zero and fuck up
            a[j] = sum(cur[minzero(j-(polynom-1)):j+1])
        # adds to triangle
        triangle.append(a)
    return triangle

# Expands a polynomial by pairing the exponent with the coefficient
def expandPolynom(level,minpow,maxpow):
    # gets the polynomial level independent of the range (so 4-6 would be x^2 essentially)
    polynom = maxpow-minpow+1
    # modifier for higher exponents
    mod = minpow*level-1
    # Gets the full set of exponents for variables; the maxpow+3 is to catch the error with lower nums
    fullpows = [i+mod for i in range(1,(polynom-1)*level+2)]
    return fullpows, polynom

def zipTime(level,fullpows,polynom):
    # Gets the coefficients
    coeffs = pascalsTriangleFull(level,polynom)[-1]
    # Zip time!!!
    zipped = list(zip(fullpows,coeffs))
    together = {f:c for f,c in zipped}
    return together


def subPowers(powsone, powstwo):
    newPows = {}
    powmax = max(powsone)
    #print("p1",powsone)
    #print("p2",powstwo)
    for i in range(powmax+1):
        if i in powsone:
            if i in powstwo:
                comb = powsone[i] - powstwo[i]
                if comb > 0:
                    newPows[i] = comb
            else:
                newPows[i] = powsone[i]
    #print("np",newPows,"\n")
    return newPows

def xMinusK(pows,k):
    newPows = {}
    powmax = max(pows)
    #print("p",pows)
    #print("k",k)
    #print("pows",pows)
    for i in range(powmax+1):
        if i in pows:
            newPows[i-k] = pows[i]
    #print("np",newPows,'\n')
    return newPows

def sumSet(powSet):
    newPows = {}
    for s in powSet:
        powmax = max(s)
        for i in range(powmax+1):
            if i in s:
                newPows[i] = newPows.get(i,0)+s[i]
    return newPows

def nextDict(pows,num,drop,minval):
    #print(pows)
    fullpows = expandPolynom(num,pows[0],pows[-1])
    #print(fullpows)
    powsWithCoeffs = zipTime(num,fullpows[0],fullpows[1])
    subpows = expandPolynom(num,pows[1],pows[-1])
    powsSub = zipTime(num+drop,subpows[0],subpows[1])
    fixedPows = subPowers(powsWithCoeffs,powsSub)
    #print("fp before",fixedPows)
    fixedPows = xMinusK(fixedPows,minval)
    #print("fp",fixedPows,'\n')
    return fixedPows

def getnextDict(pows,num,drop,minval):
    print("pows",pows)
    #print(pows)
    fullpows = expandPolynom(num,pows[0],pows[-1])
    print("fullpows",fullpows)
    #print(fullpows)
    powsWithCoeffs = zipTime(num,fullpows[0],fullpows[1])
    subpows = expandPolynom(num,pows[1],pows[-1])
    print("subpows",subpows,'\n')
    powsSub = zipTime(num+drop,subpows[0],subpows[1])
    fixedPows = subPowers(powsWithCoeffs,powsSub)
    #print("fp before",fixedPows)
    #fixedPows = xMinusK(fixedPows,minval)
    #print("fp",fixedPows,'\n')
    return fixedPows

# Calculates probability set
def probs(num,type,drop,minval):
    pows = [i+1 for i in range(0,type)] # get basic power set
    allDicts = [] # set up dicts for use with sumSet
    # Loop through the sub power sets
    for i in range(1,len(pows)):
        #print(i)
        #print(pows[i:])
        allDicts.append(nextDict(pows[i-1:],num,drop,i))
    newPows = sumSet(allDicts)
    #print(newPows)
    prob = ((1/type)**num)*newPows[minval]
    return prob

# Calculates probability set
def getPows(num,type,drop):
    pows = [i+1 for i in range(0,type+1)] # get basic power set
    allDicts = [] # set up dicts for use with sumSet
    # Loop through the sub power sets
    for i in range(1,len(pows)):
        #print(i)
        #print(pows[i:])
        allDicts.append(getnextDict(pows[i-1:],num,drop,i))
    newPows = sumSet(allDicts)
    for d in allDicts:
        print(d)
    return newPows





if __name__=="__main__":
    vals = []
    for i in range(3,19):
        '''print("pascals triangle with 4 levels and number",i)
        triangle = pascalsTriangleFull(4,i)
        print(triangle[-1])
        print("\n")
        expanded = (expandPolynom(4,i,6))
        zipped = zipTime(4,expanded[0],expanded[1])'''
        #print(i,probSet(4,6,0,i))
        #print(i,probs(4,6,1,i),'\n')
        vals.append(probs(4,6,1,i))
    for i in range(0,len(vals)):
        print(i+3,vals[i])
    print("sum",sum(vals))
    p = getPows(4,6,1)
    for i in p:
        print("pow:",i,"- coeff:",p[i])
    '''print("================================================")
    print("\nbinom")
    triangle = pascalsTriangleFull(4,2)
    for line in triangle:
        print(line)
    print("\n================================================")
    print("\ntrinom")
    triangle = pascalsTriangleFull(4,3)
    for line in triangle:
        print(line)
    print("\n================================================")
    print("\nquadrinom")
    triangle = pascalsTriangleFull(4,4)
    for line in triangle:
        print(line)
    print("\n================================================")
    print("\npentanom")
    triangle = pascalsTriangleFull(3,5)
    for line in triangle:
        print(line)
    for i in range(5):
        print("\nmin pow",i+1,"max pow",2+i)
        for j in range(1,4):
            print("level",j)
            pows = expandPolynom(j,1+i,2+i)
            print(pows)'''

    '''pows = expandPolynom(4,2,3)
    zipped = zipTime(4,pows[0],pows[1])
    print(zipped)
    pows = expandPolynom(4,2,3)
    zipped = zipTime(4,pows[0],pows[1])
    print(zipped)'''

    '''for i in range(7):
        stuff = probSet(4,6,i)
        print(stuff,"\n")'''