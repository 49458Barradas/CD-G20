import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


def geoProg(n, u, r):
    x = [0 in range(n)]
    y = [0 in range(n)]
    for i in range(n+1):
        x[i - 1] = i
        y[i - 1] = u * (r ** (i - 1))
    fig, ax = plt.subplots()
    ax.plot(x, y)
    plt.show()


def mdc(a, b):
    resto = a % b
    while resto != 0:
        resto = b % a
        b = a
        a = resto
    return b


def readFile(path_to_file):
    with open(path_to_file, "r") as file:
        content = file.read()
    return content

def mostFreqSymb(path_to_file):
    content = readFile(path_to_file)
    asciiLetter = []
    asciiCount = []
    for i in range(len(content)):
        if content[i] in asciiLetter:
            asciiCount[asciiLetter.index(content[i])] += 1
        else:
            if content[i] != ' ' and content[i] != '\n':
                asciiLetter += [content[i]]
                asciiCount += [1]
    menor = len(asciiCount)-1
    maior = 0
    maiorArr = []
    menorArr = []
    for i in range(len(asciiCount)):
        if asciiCount[i] > asciiCount[maior]:
            maiorArr = [i]
            maior = i
        if (asciiCount[i] == asciiCount[maior]):
            maiorArr += [i]
        if asciiCount[i] < asciiCount[menor]:
            menor = i
            menorArr = [i]
        if (asciiCount[i] == asciiCount[menor]):
            menorArr += [i]
    print("The most frequent symbol is ", end="")
    for i in range(len(maiorArr)):
        print(f"{asciiLetter[maiorArr[i]]}, ", end="")
    print(f"and it appeared {asciiCount[maior]} times.")
    print(f"The least frequent symbol is ", end="")
    for i in range(len(menorArr)):
        print(f"{asciiLetter[menorArr[i]]}, ", end="")
    print(f"and it appeared {asciiCount[menor]} times.")


def exerD(path_to_file):
    if path_to_file.endswith(".bmp"):
        imagem = Image.open(path_to_file)
        #converter a escala de cinza
        imagem = imagem.convert('L')
        imagem_array = np.array(imagem)
        #freq
        pixel_values, pixel_counts = np.unique(imagem_array, return_counts=True)
        #entropia
        entropia = 0
        total_pixels = imagem_array.size
        for count in pixel_counts:
            p = count / total_pixels
            print(f"o valor de informação própria de {count}: {np.log2(1/(count/len(pixel_counts)))}")
            entropia -= p * np.log2(p)
        fig, ax = plt.subplots()
        ax.hist(imagem_array.flatten(), bins=256, range=(0, 255))
        plt.show()
        print(f"A entropia da imagem é {entropia}")
    else:
        content = readFile(path_to_file)
        asciiLetter = []
        asciiCount = []
        for i in range(len(content)):
            if content[i] in asciiLetter:
                asciiCount[asciiLetter.index(content[i])] += 1
            else:
                if content[i] != ' ' and content[i] != '\n':
                    asciiLetter += [content[i]]
                    asciiCount += [1]
        #entropia
        entropia = 0
        for i in range(len(asciiCount)):
            entropia += (asciiCount[i]/len(content))*np.log2(1/(asciiCount[i]/len(content)))
            print(f"o valor de informação própria de {asciiLetter[i]}: {np.log2(1/(asciiCount[i]/len(content)))}")
        print(f"O valor de entropia é {entropia}")
        fig, ax = plt.subplots()
        ax.plot(asciiLetter, asciiCount)
        plt.show()


def main():
    mostFreqSymb("texto.txt")
    mostFreqSymb("alice29.txt")
    exerD("a.txt")
    exerD("alice29.txt")
    exerD("cp.htm")
    exerD("lena.bmp")
    exerD("Person.java")
    exerD("progc.c")



if __name__ == "__main__":
    main()
