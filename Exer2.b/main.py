import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

def readFile(path_to_file):
    with open(path_to_file, "r") as file:
        content = file.read()
    return content

def exer2b(path_to_file):
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
    # calcular da entropia
    entropia = 0
    ocorrencias = 0
    for i in range(len(asciiCount)):
        ocorrencias+=asciiCount[i]
    for i in range(len(asciiCount)):
        entropia += (asciiCount[i] / len(content)) * np.log2(1 / (asciiCount[i] / len(content)))
        print(f"A percentagem de ocorrência do símbolo: {asciiLetter[i]}: {(asciiCount[i]/ocorrencias) * 100}%")
    print(f"O valor de entropia é {entropia}")
    fig, ax = plt.subplots()
    ax.plot(asciiLetter, asciiCount)
    plt.show()

def main():
    exer2b("ListaPalavrasEN.txt")
    #exer2b("ListaPalavrasPT.txt")

if __name__ == "__main__":
    main()
