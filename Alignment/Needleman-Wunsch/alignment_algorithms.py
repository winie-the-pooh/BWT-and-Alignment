import numpy as np

def Needleman_Wunsch(reference,read,match_score = 1, mismatch_score = -1,Gap_penalty = -1):
    str1 = reference
    str2 = read

    M = np.zeros([len(str1)+1,len(str2)+1])
    M[0,1:] = np.array(range(1,len(str2)+1))*Gap_penalty
    M[1:,0] = np.array(range(1, len(str1) + 1)) * Gap_penalty
    for i in range(1,len(str1)+1):
        for j in range(1,len(str2)+1):

            M[i][j] = max(M[i-1][j] + Gap_penalty,M[i][j - 1] + Gap_penalty,
                          M[i-1][j-1] + match_score if str1[i-1] == str2[j-1] else M[i-1][j-1] + mismatch_score)
    # print(M)

    A = ''
    B = ''
    CIGAR_SCORE = ''
    status = None
    count = 0

    cur = (len(str1),len(str2))
    score = M[cur[0],cur[1]]
    while cur[0] != 0 or cur[1] != 0:

        if M[cur[0],cur[1]] == (M[cur[0],cur[1]-1] + Gap_penalty):
            # insertion
            if status == 1: # 1 for insertion
                count+=1
            else:
                CIGAR_SCORE = 'I' + str(count) + CIGAR_SCORE
                status = 1
                count = 1

            A = '_' + A
            B = str2[cur[1]-1] + B
            cur = (cur[0], cur[1] - 1)
        elif str1[cur[0]-1] == str2[cur[1]-1] and M[cur[0],cur[1]] == (M[cur[0]-1,cur[1]-1] + match_score):
            # match
            if status == 2: # 2 for match
                count+=1
            else:
                CIGAR_SCORE = 'M' + str(count) + CIGAR_SCORE
                status = 2
                count = 1

            A = str1[cur[0]-1] + A
            B = str2[cur[1]-1] + B
            cur = (cur[0]-1,cur[1]-1)
        elif str1[cur[0] - 1] != str2[cur[1] - 1] and M[cur[0], cur[1]] == (M[cur[0] - 1, cur[1] - 1] + mismatch_score):
            # mismatch
            if status == 3: # 3 for mismatch
                count+=1
            else:
                CIGAR_SCORE = 'X' + str(count) + CIGAR_SCORE
                status = 3
                count = 1

            A = str1[cur[0] - 1] + A
            B = str2[cur[1]-1] + B
            cur = (cur[0] - 1, cur[1] - 1)
        elif M[cur[0],cur[1]] == (M[cur[0]-1,cur[1]] + Gap_penalty):
            # deletion
            if status == 4: # 4 for deletion
                count+=1
            else:
                CIGAR_SCORE = 'D' + str(count) + CIGAR_SCORE
                status = 4
                count = 1

            A = str1[cur[0] - 1] + A
            B = '_' + B
            cur = (cur[0] - 1, cur[1])
    if not count == 0:
        CIGAR_SCORE = str(count) + CIGAR_SCORE
    return A,B,CIGAR_SCORE[:-1],score