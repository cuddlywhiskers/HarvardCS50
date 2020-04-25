from cs50 import get_int

# compiles all codes
def main():
    n = get_integer()
    print_blocks(n)
    print(end="")


# Gets integar from user command prompt
def get_integer():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

# print blocks depending on input
def print_blocks(n):
    for i in range(n):
        print(" " * (n-i-1) + "#" * (i+1))


main()
