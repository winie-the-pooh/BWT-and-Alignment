import data_generator
import alignment_algorithms
import time


ref,read,cigar,score = alignment_algorithms.Needleman_Wunsch('AATTTCGA','AATTCAA')

print(ref)
print(read)
print(cigar)
print(score)


# repeat = 10
# with open('NW_res','w') as f:
#     for i in range(10,51):
#         t = []
#         for j in range(10):
#             a = data_generator.reference_data(i)
#             b = data_generator.read_reference(a)
#
#             cur = time.time()
#             alignment_algorithms.Needleman_Wunsch(a,b)
#             t.append(str(time.time()-cur))
#         f.write(','.join(t) + '\n')
