import math
import random
import string

utfL = 2 ** 8

def entropia(str):
    length = len(str)
    letters = []
    counts = []
    entropia = 0
    for i in str:
        if i in letters:
            counts[letters.index(i)] += 1
        else:
            letters.append(i)
            counts.append(1)
    for i in letters:
        p = counts[letters.index(i)] / length
        entropia += (p * math.log2(p)) * -1
    return entropia


def b(n):
    #lista de símbolos com representação UTF-8
    utf8_symbols = list(range(0x0020, 0x007F)) + list(range(0x00A0, 0x00FF))
    seq = ''.join([chr(random.choice(utf8_symbols)) for _ in range(n)])
    print(seq)
    # Entropia da fonte
    p = 1 / len(utf8_symbols)
    entrp_fonte = (p * math.log2(p)) * len(utf8_symbols) * -1
    print(entrp_fonte)
    # Entropia gerada
    print(entropia(seq))


def generate_password():
    length = random.randint(8, 12)
    characters = string.ascii_letters + string.digits + string.punctuation
    password = ''.join(random.choice(characters) for i in range(length))
    return password

def main():
    b(10)
    print(generate_password())

if __name__ == '__main__':
    main()