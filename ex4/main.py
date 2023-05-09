import numpy as np
from matplotlib import pyplot as plt

from Lab1.PythonPart.main import exerD
import random

constantKey = 3333333
plainText = "abcabcd"

def makeVernamCypher(plainText, theKey):
    key_bytes = bytearray(str(theKey), 'utf-8') * (len(plainText) // len(str(theKey))) + bytearray(str(theKey)[:len(plainText) % len(str(theKey))], 'utf-8')
    output_string = ''.join(chr(c ^ k) for c, k in zip(plainText.encode(), key_bytes))
    return output_string

def vernamTxtConstant(path_to_file, theKey):
    with open(path_to_file, 'rb') as f:
        plaintext_bytes = f.read()
        f.close()
    key_bytes = bytearray(str(theKey), 'utf-8') * (len(plaintext_bytes) // len(str(theKey))) + bytearray(str(theKey)[:len(plaintext_bytes) % len(str(theKey))], 'utf-8')
    ciphertext_bytes = bytearray([b1 ^ b2 for b1, b2 in zip(plaintext_bytes, key_bytes)])
    output = ciphertext_bytes.decode('utf-8')
    writeFile("output.txt", output)
    return output

def vernamTxtRandom(path_to_file):
    with open(path_to_file, 'rb') as f:
        plaintext_bytes = f.read()
        f.close()
    key_length = len(plaintext_bytes)
    key_bytes = bytearray(random.randint(0, 255) for _ in range(key_length))
    ciphertext_bytes = bytearray([b1 ^ b2 for b1, b2 in zip(plaintext_bytes, key_bytes)])
    with open("output_random.txt", 'wb') as f:
        f.write(ciphertext_bytes)


def writeFile(path_to_file, content):
    with open(path_to_file, "w") as file:
        file.write(content)
        file.close()

def entropia(path_to_file):
    with open(path_to_file, 'rb') as f:
        content = f.read()
        f.close()
    asciiLetter = []
    asciiCount = []
    for i in range(len(content)):
        if content[i] in asciiLetter:
            asciiCount[asciiLetter.index(content[i])] += 1
        else:
            if content[i] != ' ' and content[i] != '\n':
                asciiLetter += [content[i]]
                asciiCount += [1]
    # calcular da entropia
    entropia = 0
    for i in range(len(asciiCount)):
        entropia += (asciiCount[i] / len(content)) * np.log2(1 / (asciiCount[i] / len(content)))
        if 32 <= asciiLetter[i] <= 126:
            asciiLetter[i] = chr(asciiLetter[i])
        else:
            asciiLetter[i] = f"i{i}"
        #entropia += (asciiCount[i] / len(content)) * np.log2(1 / (asciiCount[i] / len(content)))
        print(f"o valor de informação própria de {asciiLetter[i]}: {np.log2(1 / (asciiCount[i] / len(content)))}")
    print(f"O valor de entropia é {entropia}")
    fig, ax = plt.subplots()
    fig.set_size_inches(70, 5)
    ax.plot(asciiLetter, asciiCount)
    plt.show()

def exer4b():
    ficheiro_de_teste = "alice29.txt"
    #teste constante
    exerD(ficheiro_de_teste)
    output0= vernamTxtConstant(ficheiro_de_teste, constantKey)
    #writeFile("output.txt", output0)
    #exerD("output.txt")
    #print("\n \n \n \n")
    #teste random
    #exerD(ficheiro_de_teste)
    #output1 = vernamTxtRandom(ficheiro_de_teste)
    #writeFile("output.txt", output1)
    #exerD("output.txt")


def main():
    #vernamTxtConstant("alice29.txt", constantKey)
    #exerD("output.txt")
    #vernamTxtRandom("alice29.txt")
    #entropia("output_random.txt")
    #exerD("output.txt")
    entropia("output_random.txt")


if __name__ == "__main__":
    main()