import sys
import csv


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    dna = []
    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            dna.append(row)

    with open(sys.argv[2]) as txt_file:
        sequence = txt_file.read()

    strs_in_sequence = []
    strs_in_dna = []
    output = "No match"
    for i in range(len(dna)):
        for str in dna[i]:
            if str != "name":
                str_repeats = calculate_longest_run_of_consecutive_repeats(sequence, str)
                strs_in_sequence.append(str_repeats)
                strs_in_dna.append(int(dna[i][str]))
        if strs_in_sequence == strs_in_dna:
            output = dna[i]["name"]
        else:
            strs_in_sequence.clear()
            strs_in_dna.clear()
    
    print(output)


def calculate_longest_run_of_consecutive_repeats(sequence, str):
    iteration_index = len(str)
    repeats_counter = 0
    maximum_repeats = 0
    start_of_str = 0
    end_of_str = len(str)

    while True:
        if sequence[start_of_str:end_of_str] == str and end_of_str != len(sequence):
            repeats_counter += 1
            start_of_str += iteration_index
            end_of_str += iteration_index
        elif sequence[start_of_str:end_of_str] != str and end_of_str != len(sequence):
            start_of_str += 1
            end_of_str += 1
            if maximum_repeats < repeats_counter:
                maximum_repeats = repeats_counter
            repeats_counter = 0
        else:
            break

    return maximum_repeats


if __name__ == "__main__":
    main()
