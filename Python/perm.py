# /usr/bin python
import numpy as np

##This is code by Lukas Kjäll (https://github.com/statisticalbiotechnology/exactpermutation) slightly modified by @m_hoehl to get the one-sided version of the test
def significance_of_mean(a,b,num_bin = 200, data_type=np.float64): #

    # discretize
    ab = np.sort(np.concatenate((a, b), axis=None))[::-1] #sort descending (biggest first)
    bins = np.linspace(min(ab), max(ab), num_bin)
    digitized = np.digitize(ab, bins)
    if len(a)>len(b):
        score = sum(np.digitize(b,bins))
    else:
        score = sum(np.digitize(a,bins))
    K = min(len(a),len(b))
    S = np.sum(digitized[0:K])+1 #hoehle: This is the maximum sum we can get! why +1? A: S is the number of bins, lowest score=0, highest score=sum(digitiyzed) make a total of sum(digitiyzed)+1 bins
    L = len(ab) #length of m+n
    NN = score_distribution_numpy(digitized, K, S, L, data_type)
    # Total number of configurations
    total = np.sum(NN)
    # Just the one sided version of the test, i.e. alternative="greater"
    if len(a)>len(b):
        more_extreme = np.sum(NN[:score])
    else:
        more_extreme = np.sum(NN[score:])
    p = more_extreme/total
    return p, total, more_extreme

def score_distribution_numpy(digitized,K,S,L, data_type=np.float64):
    # N(s,l) number of ways to reach a sum of s using k of the l first readouts
    # Calculated by iterating over the
    Nold = np.zeros((S,L), dtype=data_type)
    # Initiating (i.e. k=0 case)
    for l in range(L):
        d=digitized[l]
        Nold[d,l] = data_type(1)
    # Do each of the other picks
    for k in range(1,K):
        Nnew = np.zeros((S,L), dtype=data_type)
        C = np.zeros((S,1), dtype=data_type)
        for l in range(1,L): #hoehle: why 1:L and not 0:L?
            d = digitized[l]
            C +=  Nold[:,l-1:l]
            Nnew[d:S,l] = C[0:S-d,0]
        Nold = Nnew
    NN = np.sum(Nold,axis=1)
    return NN

if __name__ == "__main__":
    import argparse
    import sys
    import pandas as pd
    import numpy.random as rnd
    import scipy.stats as stat

    ##Try the Python approach 
    a = np.array([0, 3, 0])
    b = np.array([5, 2, 1])
    ab = np.sort(np.concatenate((a, b), axis=None))

    print(a)
    print(b)
    print(ab)
    print(len(ab))
    #    a= rnd.normal(0.0, 1.0, 50)
    #    b= rnd.normal(0.7, 1.0, 50)
    print(significance_of_mean(a, b, num_bin=11))
