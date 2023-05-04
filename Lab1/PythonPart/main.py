import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


def geoProg(n, u, r):
    x = [0 in range(n)]
    y = [0 in range(n)]
    for i in range(n + 1):
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


def mostFreqSymb(path_to_file): #so retorna um valor dos dois lados nem que existam multiplos valores com cena identica
    content = readFile(path_to_file)  # leitura do ficheiro
    asciiLetter = []  # guarda as letras/simbolos existentes na contagem
    asciiCount = []  # guarda o número de vezes que determinado simbolo apareceu (idx partilhado entre estes 2 arrays)
    for i in range(len(content)):
        if content[i] in asciiLetter:
            asciiCount[asciiLetter.index(content[i])] += 1
        else:
            if content[i] != ' ' and content[i] != '\n':
                asciiLetter += [content[i]]
                asciiCount += [1]
    menor = len(asciiCount)-1
    maior = -1
    for i in range(len(asciiCount)):
        if asciiCount[i] > asciiCount[maior]:
            maior = i
        if asciiCount[i] < asciiCount[menor]:
            menor = i
    print(f"The most frequent symbol is {asciiLetter[maior]} and it appeared {asciiCount[maior]} times.")
    print(f"The least frequent symbol is {asciiLetter[menor]} and it appeared {asciiCount[menor]} times.")

def mostFreqSymbDrained(path_to_file):
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
        # abrir o arquivo BMP
        imagem = Image.open(path_to_file)

        # converter a imagem em modo escala de cinza
        imagem = imagem.convert('L')

        # obter os dados da imagem como um array numpy
        imagem_array = np.array(imagem)

        # contar a frequência de cada valor de pixel na imagem
        pixel_values, pixel_counts = np.unique(imagem_array, return_counts=True)

        # calcular a entropia
        entropia = 0
        total_pixels = imagem_array.size
        for count in pixel_counts:
            p = count / total_pixels
            print(f"o valor de informação própria de {count}: {np.log2(1/(count/len(pixel_counts)))}")
            entropia -= p * np.log2(p)
        print(f"Valor da entropia é {entropia}")
        # plotar o histograma da imagem
        fig, ax = plt.subplots()
        ax.hist(imagem_array.flatten(), bins=256, range=(0, 255))
        plt.show()

        # imprimir a entropia
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
        #calcular da entropia
        entropia = 0
        for i in range(len(asciiCount)):
            entropia += (asciiCount[i]/len(content))*np.log2(1/(asciiCount[i]/len(content)))
            print(f"o valor de informação própria de {asciiLetter[i]}: {np.log2(1/(asciiCount[i]/len(content)))}")
        print(f"O valor de entropia é {entropia}")
        fig, ax = plt.subplots()
        ax.plot(asciiLetter, asciiCount)
        plt.show()


def main():
    #exerD("a.txt")
    #exerD("alice29.txt")
    #exerD("cp.htm")
    exerD("lena.bmp") #AQUI EXISTE ERRO PORQUE UM FICHEIRO BMP n pode ser lido da mesma forma
    #exerD("Person.java")
    #exerD("progc.c")


if __name__ == "__main__":
    main()
