from cs50 import get_float

# Compile main
def main():
    n = get_amount()
    counter = change(n)
    print(counter)

# get amount using command prompt
def get_amount():
    while True:
        n = get_float("Changed owed: ")
        if n >= 0:
            break

    n = n*100

    return n

# return change
def change(n):
    counter = 0

    while True:
        if n >= 25:
            counter += 1
            n = n - 25
        else:
            break

    while True:
        if n >= 10:
            counter += 1
            n = n - 10
        else:
            break

    while True:
        if n >= 5:
            counter += 1
            n = n - 5
        else:
            break

    while True:
        if n >= 1:
            counter += 1
            n = n - 1
        else:
            break

    return counter

# print main
main()
