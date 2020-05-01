from cs50 import get_string
import re

# Compile all codes
def main():
    text = get_text()
    calculate_index(text)

# Prompt user to input text at command line
def get_text():
    text = get_string("Text: ")
    return text

def calculate_index(text):

    text = text.rstrip("\n")

    words = len(text.split(" "))
    sentences = len(re.split("\?|\!|\.", text)) - 1
    letter = 0

    for i in text:
        if re.search("[a-zA-Z]", i):
            letter += 1

    L = letter / (words/100)
    S = sentences / (words/100)

    index = 0.0588 * L - 0.296 * S - 15.8

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")

main()
