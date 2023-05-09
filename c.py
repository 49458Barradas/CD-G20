import random
import string


def generate_password():
    length = random.randint(8, 12)
    characters = string.ascii_letters + string.digits + string.punctuation
    password = ''.join(random.choice(characters) for i in range(length))
    return password

def main():
    print(generate_password())

if __name__ == '__main__':
    main()