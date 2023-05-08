import random
import numpy as np

def bsc(path_to_file, BER):
    with open(path_to_file, 'rb') as f:
        data = f.read()
        f.close()
    data_bits = ''.join(format(byte, "08b") for byte in data)
    output_bits = ''
    for bit in data_bits:
        if random.random() < BER:
            output_bits += '0' if bit == '1' else '1'
        else:
            output_bits += bit
    output_bytes = bytes(int(output_bits[i:i+8], 2) for i in range(0, len(output_bits), 8))
    with open("testeOUT.txt", "wb") as f:
        f.write(output_bytes)
        f.close()

def calculate_BER(file1, file2):
    with open(file1, 'rb') as f1:
        data1 = f1.read()
    with open(file2, 'rb') as f2:
        data2 = f2.read()
    bit_diff = 0
    for byte1, byte2 in zip(data1, data2):
        for i in range(8):
            bit1 = (byte1 >> i) & 1
            bit2 = (byte2 >> i) & 1
            if bit1 != bit2:
                bit_diff += 1
    ber = bit_diff / (len(data1) * 8)
    return ber

''''
def main():
    #bsc("testeIN.txt", 0.0001)
    #t = calculate_BER("testeIN.txt", "testeOUT.txt")
    #print(t)

if __name__ == '__main__':
    main()
'''