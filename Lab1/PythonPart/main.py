import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np


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
    print(f"O valor de entropia é {entropia}")
    fig, ax = plt.subplots()
    ax.plot(asciiLetter, asciiCount)
    plt.show()


def main():
    mostFreqSymb("texto.txt")
    print()
    mostFreqSymbDrained("texto.txt")
    print()
    exerD("texto.txt")


if __name__ == "__main__":
    main()
