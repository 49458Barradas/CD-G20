import random

import numpy as np


def bsc(binSeq, BER):
    seqL = len(str(binSeq))
    p = BER
    output = []
    for i in range(seqL):
        temp = random.random()
        if temp < p:
            if binSeq[i] == '1':
                output.append('0')
            else:
                output.append('1')
        else:
            output.append(binSeq[i])
    return ''.join(output)


def getBER(bin_seq, output):
    l = len(bin_seq)
    count = 0
    for i in range(0, l):
        if output[i] != bin_seq[i]:
            count+=1
    print(f"count = {count}")
    print(f"length = {l}")
    ber = count / l
    print(f"ber = {ber}")
    return ber

def interleaving(str, row = 0, col = 0):
    length = len(str)
    '''
    if row * col == 0:
        mV = int(np.ceil(np.sqrt(length)))
        mtxDim = (mV ** 2)
        extra = mtxDim - length
        mtx = list(str)
        while extra > 0:
            mtx.append('')
            extra -= 1
        matrix = np.empty((mV, mV), dtype='U1')
        for i in range(len(mtx)):
            row = i // mV
            col = i % mV
            matrix[row, col] = mtx[i]
        print(matrix)
        matrix = matrix.T
        lst = []
        for i in range(mtxDim):
            rows = i // mV
            cols = i % mV
            if matrix[rows, cols] != "":
                lst.append(matrix[rows, cols])
        return "".join(lst)
    else:
    '''
    mtxL = row * col
    if mtxL < length:
        raise ValueError("str tem que ter dimensão igual ou inferior à matriz")
    extras = mtxL - length
    mtx = list(str)
    while extras > 0:
        mtx.append('')
        extras -= 1
    matrix = np.empty((row, col), dtype='U1')
    for i in range(len(mtx)):
        rows = i // col
        cols = i % col
        matrix[rows, cols] = mtx[i]
    matrix = matrix.T
    lst = []
    for i in range(mtxL):
        rows = i // row
        cols = i % row
        if matrix[rows, cols] != "":
            lst.append(matrix[rows, cols])
    return "".join(lst)

def exer5bii(input, BER):
    teste = interleaving(input,8,4)
    print(f"Interleaving returns {teste}")
    print("\n")
    seqBin = ''.join(format(ord(c), '08b') for c in teste)
    print(f"Conversão em binário {seqBin}")
    print("\n")
    teste1 = bsc(seqBin, BER)
    print(f"Após BSC {teste1}")
    print("\n")
    spaced_str = ' '.join([teste1[i:i + 8] for i in range(0, len(teste1), 8)])
    teste2 = ''.join([chr(int(byte, 2)) for byte in spaced_str.split()])
    print(f"Conversão de novo a utf-8 {teste2}")
    teste3 = interleaving(teste2,4,8)
    print("\n")
    print(f"De-interleaved é {teste3}")

def main():
    input = "ExemploDeTransmissaoInterleaving"
    print(f"{input} \n")
    exer5bii(input, 0.001)

if __name__ == '__main__':
    main()
