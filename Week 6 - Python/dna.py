import csv
from sys import argv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    with open(argv[1]) as csv_file:
        # csv_reader is now a list of strings in the csv file (row by row)
        csv_reader = csv.reader(csv_file)
        rows = iter(csv_reader)
        # like a for loop that will iterate over each row when called, [1:] denotes skipping the first value in the row
        # in this case, only called once and therefore only looks at first row which denotes the sub_str's for the DNA
        all_sequences = next(rows)[1:]

        with open(argv[2]) as txt_file:
            s = txt_file.read()
            # creating a list (array) that stores the # of times each sequence is repeated for the string in the text file ["15", "13", "12", "45"] ~ ["AGAT", "AATT" ...]
            # sub_str = range of all_sequences * basically like this
            actual = [max_repeat(s, sub_str) for sub_str in all_sequences]

        # looping through every row in the csv
        for row in csv_reader:
            person = row[0]
            # turn every value in the row into an integer skipping the first value which is the name
            value = [int(val) for val in row[1:]]
            if actual == value:
                print(person)
                exit(0)
        print("No match")


def max_repeat(s, sub):
    # s:    [ATATATTATAT]
    # ans:  [30201002010]
    # sub: AT

    ans = [0] * len(s)

    # for loop starting at the length of the sub to check first substring going through entire string
    for i in range(len(s) - len(sub), -1, -1):
        if s[i: i + len(sub)] == sub:
            if (i + len(sub)) > (len(s) - 1):
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]

    return max(ans)


main()