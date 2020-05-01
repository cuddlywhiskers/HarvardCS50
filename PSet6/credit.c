from cs50 import get_int

# compile all codes
def main():
    n = get_number()
    validate(n)

# Get credit card number
def get_number():
    n = get_int("Number: ")
    return n

# check credit card number
def validate(number):
    length = len(str(number))

    checksum = 0
    divider = 100
    mod = 10

    # Every alternative digit starting from the last digit
    n = number
    while True:
        if n >= 1:
            checksum += (n % mod)
            n = int(n / divider)
        else:
            break

    # Every alternative digit starting from the second last digit
    m = int (number / 10)         # Strip of the last digit before looping
    while True:
        if m >= 1:
            tmp = (m % mod) * 2
            m = int(m / divider)

            # if tmp >= 10, split the number and add it into checksum
            if tmp >= 10:
                checksum += (tmp % mod)
                checksum += int(tmp / 10)

            else:
                checksum += tmp

        else:
            break

    # mod of checksum
    mod_checksum = checksum % mod
    check(number, length, mod_checksum)

# Check card validity with conditions
def check(number, length, mod_checksum):

    amex = [34, 37]
    visa_length = [13, 16]
    master = [51, 52, 53, 54, 55]

    first_digit = int(number / pow(10, (length - 1)))
    first_two_digit = int(number / pow(10, (length - 2)))

    if first_two_digit in amex and length == 15 and mod_checksum == 0:
        print("AMEX")
    elif length in visa_length and first_digit == 4 and mod_checksum == 0:
        print("VISA")
    elif first_two_digit in master and length == 16 and mod_checksum == 0:
        print("MASTERCARD")
    else:
        print("INVALID")

# main
main()
