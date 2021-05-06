from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# main height-based loop
for i in range(height):

    # left piramid loop
    for j in range(height - (i + 1)):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")

    # Separation of the piramids
    print("  ", end="")

    # right piramid loop
    for j in range(i + 1):
        print("#", end="")

    print("")

