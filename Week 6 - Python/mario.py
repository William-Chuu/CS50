from cs50 import get_int


def main():
    # main function
    n = get_height()
    for i in range(1, n + 1):
        print((" " * (n - i)) + ("#" * i) + (" " * 2) + ("#" * i))


def get_height():
    # height between 1-8 inclusive
    while True:
        n = get_int("Height: ")
        if 1 <= n <= 8:
            break
    return n


main()

