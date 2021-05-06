import sys
import csv

database = []
strs = []


def main():
    argv = sys.argv
    argc = len(argv)

    if argc != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    load(argv[1])
    update_frequency(argv[2])

    # Create local variable to make comparisons easier
    strs_resume = []
    for dna_str in strs:
        strs_resume.append(dna_str['frequency'])

    # Compare frequency #3
    for profile in database:
        if profile['frequency'] == strs_resume:
            print(profile['name'])
            sys.exit(0)
    print('No match')


# Load csv file into memory #1
def load(data_path):
    # open file
    with open(data_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        row_count = 0
        # storing csv data in our globals variables
        for row in csv_reader:
            if row_count == 0:
                for i in range(1, len(row)):
                    dna_str = {
                        'str': row[i],
                        'frequency': 0
                    }
                    strs.append(dna_str)
            else:
                profile = {
                    'name': row[0],
                    'frequency': [int(str) for str in row[1:len(row)]]
                }
                database.insert(row_count, profile)
            row_count += 1


# Update frequencies of the data file in memory #2
def update_frequency(sequence_filepath):

    # open file
    with open(sequence_filepath) as sequence_file:
        sequence = sequence_file.read()

    # Analyse the data comparing each str
    for i in range(len(strs)):
        # temporary variables
        frequencies = []
        found = False
        tmp_frequency = 0
        j = 0

        # main loop on the data
        while j != len(sequence):
            # this offset prevents collapsing between inside str's
            offset = j + len(strs[i]['str'])
            # logic to find only neighbor str's
            if found == True:
                if sequence[j:offset] == strs[i]['str']:
                    tmp_frequency += 1
                    j += len(strs[i]['str']) - 1
                else:
                    frequencies.append(tmp_frequency)
                    found = False
                    tmp_frequency = 0
            else:
                if sequence[j:offset] == strs[i]['str']:
                    j += len(strs[i]['str']) - 1
                    tmp_frequency += 1
                    found = True
            j += 1

        # updating the global variable with the max frequency
        if frequencies == []:
            strs[i]['frequency'] = 0
        else:
            strs[i]['frequency'] = max(frequencies)


main()