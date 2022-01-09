from cs50 import get_int


def main():
    while True:
        pyramid_height = get_int("Pyramid height: ")
        if pyramid_height >= 1 and pyramid_height <= 8:
            break

    number_of_spaces = pyramid_height - 1
    number_of_hashes = 1
    for i in range(pyramid_height):
        for j in range(number_of_spaces - i):
            print(" ", end="")
        for n in range(number_of_hashes):
            print("#", end="")
        print("  ", end="")
        for m in range(number_of_hashes):
            print("#", end="")
        print()
        number_of_hashes += 1


if __name__ == "__main__":
    main()