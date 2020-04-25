from cs50 import get_int

# compile all the codes
def main():
    n = get_integer()
    print_blocks(n)
    print(end="")


# Get prompt
def get_integer():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

# Print blocks by prompt
def print_blocks(n):
    for i in range(n):
        print(" " * (n-i-1) + "#" * (i+1) + " " * (2) + "#" * (i+1))

main()
