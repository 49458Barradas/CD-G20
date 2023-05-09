import random

def gerar_arquivo_aleatorio(N, fmp, M):
    # Verifica se o tamanho do alfabeto e da função de massa de probabilidade são iguais
    if len(fmp) != len(M):
        raise ValueError("O tamanho de fmp e M devem ser iguais")

    # Cria uma lista vazia para armazenar o arquivo gerado
    arq = []

    # Gera N símbolos aleatórios baseados na função de massa de probabilidade fornecida
    for i in range(N):
        # Gera um número aleatório entre 0 e 1
        rand = random.uniform(0, 1)

        # Percorre os valores da função de massa de probabilidade para encontrar o símbolo correspondente
        prob = 0
        for j in range(len(fmp)):
            prob += fmp[j]
            if rand < prob:
                arq.append(M[j])
                break

    # Retorna o arquivo gerado como uma string
    str = ''.join(arq)
    file = open("test.txt", 'w')
    file.write(str)
    print(str)
    file.close()


def main():
    N = 100
    fmp = [0.1, 0.1, 0.1, 0.7]
    M = ['g', 'u', 'i', 'l']
    gerar_arquivo_aleatorio(N, fmp, M)

if __name__ == '__main__':
    main()