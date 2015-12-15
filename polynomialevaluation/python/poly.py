import math
import random
import time
import timeit
max_dim_poly = 40
coeff = random.sample(range(1, 100), max_dim_poly)


def polyeval(x,coeff):
    xacc = 1;
    finalValue = 0.0
    for i in xrange(0,len(coeff)):
        finalValue = finalValue + coeff[i] * xacc
        xacc = xacc * x
    return finalValue

def polyevalHorner(x,coeff):
    finalValue = 0.0
    for i in xrange(len(coeff)-1 , -1,-1):
        finalValue = finalValue * x+ coeff[i]
    return finalValue


if __name__ == '__main__':
    #first test the correctness
    result = polyeval(-0.1, [70, 39, 90, 69, 27, 53, 4, 14, 31, 29, 17, 9, 79, 47, 63, 81, 80, 34, 77, 87, 76, 11, 83, 36, 72, 6, 89, 24, 1, 22, 21, 40, 37, 92, 61, 13, 18, 5, 15, 52] )
    print("Simple result " + str(result))
    result = polyevalHorner(-0.1, [70, 39, 90, 69, 27, 53, 4, 14, 31, 29, 17, 9, 79, 47, 63, 81, 80, 34, 77, 87, 76, 11, 83, 36, 72, 6, 89, 24, 1, 22, 21, 40, 37, 92, 61, 13, 18, 5, 15, 52] )
    print("Horner result " + str(result))
    #now test the speed
    print "this is the time with simple evaluation"
    print timeit.timeit("polyeval(-0.1, [70, 39, 90, 69, 27, 53, 4, 14, 31, 29, 17, 9, 79, 47, 63, 81, 80, 34, 77, 87, 76, 11, 83, 36, 72, 6, 89, 24, 1, 22, 21, 40, 37, 92, 61, 13, 18, 5, 15, 52] )", setup="from __main__ import polyeval")

    print "this is the time with Horner evaluation"
    print timeit.timeit("polyevalHorner(-0.1, [70, 39, 90, 69, 27, 53, 4, 14, 31, 29, 17, 9, 79, 47, 63, 81, 80, 34, 77, 87, 76, 11, 83, 36, 72, 6, 89, 24, 1, 22, 21, 40, 37, 92, 61, 13, 18, 5, 15, 52] )", setup="from __main__ import polyevalHorner")
