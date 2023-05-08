import binascii
import random
from Lab1.PythonPart.main import exerD

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
    return output

def vernamTxtRandom(path_to_file):
    with open(path_to_file, 'rb') as f:
        plaintext_bytes = f.read()
        text_length = len(plaintext_bytes)

    key_bytes = bytearray(random.randint(0, 255) for _ in range(text_length))
    ciphertext_bytes = bytearray([b1 ^ b2 for b1, b2 in zip(plaintext_bytes, key_bytes)])
    output = ciphertext_bytes.decode('utf-8')
    return output

def writeFile(path_to_file, content):
    with open(path_to_file, "w") as file:
        file.write(content)
        file.close()

def exer4b():
    ficheiro_de_teste = "alice29.txt"
    #teste constante
    exerD(ficheiro_de_teste)
    output0= vernamTxtConstant(ficheiro_de_teste, constantKey)
    writeFile("output.txt", output0)
    exerD("output.txt")
    print("\n \n \n \n")
    #teste random
    #exerD(ficheiro_de_teste)
    #output1 = vernamTxtRandom(ficheiro_de_teste)
    #writeFile("output.txt", output1)
    #exerD("output.txt")

'''
def main():
    toprint = makeVernamCypher(plainText, constantKey)
    print(toprint)
    decoded = makeVernamCypher(toprint, constantKey)
    print(decoded)
    toprint = vernamTxtConstant("alice29.txt", constantKey)
    print(toprint)
    decoded = makeVernamCypher(toprint, constantKey)
    print(decoded)
    toPrint = vernamTxtRandom("alice29.txt")
    print(toprint)
    exer4b()

if __name__ == "__main__":
    main()
'''