import numpy as np
import random

def reference_data(length):
    alphabet = 'ATCG'
    ind = np.random.randint(0, len(alphabet), length)
    return ''.join([alphabet[t] for t in ind])

def read_reference(data):
    alphabet = 'ATCG'
    L = len(data)
    same_odd = 0.7

    mismatch_odd = 0.2
    insertion_odd = 0.4
    deletion_odd = 0.4
    res = ''

    i = 0
    while i < L:
        if random.random() <= same_odd:
            res += data[i]
        else:
            coin = random.random()
            # mismatch
            if coin <= mismatch_odd:
                for j in alphabet:
                    if not j == data[i]:
                        res += j
                        break

            # insertion
            elif coin <= mismatch_odd+insertion_odd:
                res += alphabet[random.randint(0,len(alphabet)-1)]
                res += data[i]

            # deletion
            else:
                pass

        i+=1


    return res
