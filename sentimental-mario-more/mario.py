import cs50

while True:
    height = cs50.get_int("Height: ")
    if height <= 8 and height > 0:
        break

spaces = height - 1


def print_row(height, space):
    for i in range(space):
        print(" ", end="")
    for i in range(height):
        print("#", end="")
    print("  ", end="")
    for i in range(height):
        print("#", end="")
    print("\n", end="")


for i in range(height):
    print_row(i + 1, spaces)
    spaces -= 1
