from cs50 import get_string


def main():
    sentence = get_sentence()

    # all = 0 except word counter to account for last word that does not have space after it
    word_counter, sent_counter, letter_counter = 1, 0, 0

    # looping over every char in sentence
    for char in sentence:
        if char.isalpha() == True:
            letter_counter += 1
        elif char == ' ':
            word_counter += 1
        elif char == '.' or char == '?' or char == '!':
            sent_counter += 1

    # average letters and sentences per 100 words
    L = letter_counter / word_counter * 100
    S = sent_counter / word_counter * 100

    # coleman-liau calc
    CL = round(0.0588 * L - 0.296 * S - 15.8)

    if CL < 1:
        print("Before Grade 1")
    elif CL >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {CL}")


def get_sentence():
    a = get_string("Text: ")
    return a


main()