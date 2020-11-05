from cs50 import get_int


def main():
    cardnum = get_cardnum()
    # convert cardnum to a string in order to count the length of it
    cardnumlen = len(str(cardnum))

    if cardnumlen != 15 and cardnumlen != 13 and cardnumlen != 16:
        print("INVALID")
        exit(1)

    cardnumodd = cardnum
    # cut off last digit
    cardnumeven = cardnum // 10

    # lists of the digits that we can sum later
    # lists so we can continuously add digits into it using a loop
    odd_digits = []
    even_digits = []

    # take into account digits >= 10 that need to be split up
    double_digits = []
    counter = 0

    # for loop over range of cardnumlen + 1 using floor divisor to get the odd number of digits no matter the number (13,15 or 16)
    for i in range(0, (cardnumlen + 1) // 2):
        # get last digit in the i th position in list
        odd_digits.insert(i, cardnumodd % 10)
        # cuts off last 2 digits to get next odd digit
        cardnumodd = cardnumodd // 100

    # even digits
    for j in range(0, cardnumlen // 2):
        even_digits.insert(j, (cardnumeven % 10) * 2)
        cardnumeven = cardnumeven // 100

    # looking for double digit numbers
    for k in range(0, cardnumlen // 2):
        if even_digits[k] >= 10:
            even_digits[k] = even_digits[k] % 10
            # for the tens spot
            counter += 1

    s_odd = sum(odd_digits)
    s_even = counter + sum(even_digits)
    s = s_odd + s_even
    smod = s % 10
    cardnumstr = str(cardnum)

    if cardnumstr[0] == '3' and (cardnumstr[1] == '4' or cardnumstr[1] == '7') and cardnumlen == 15 and smod == 0:
        print("AMEX")
    elif cardnumstr[0] == '5' and (int(cardnumstr[1]) in range(1, 6)) and cardnumlen == 16 and smod == 0:
        print("MASTERCARD")
    elif cardnumstr[0] == '4' and (cardnumlen == 13 or cardnumlen == 16) and smod == 0:
        print("VISA")
    else:
        print("INVALID")


def get_cardnum():
    while True:
        n = get_int("Number: ")
        if n > 0:
            break
    return n


main()