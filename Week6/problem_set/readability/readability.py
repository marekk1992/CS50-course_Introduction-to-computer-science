def main():
    text = input("Text: ")
    number_of_sentences = calculate_number_of_sentences(text)
    number_of_letters = calculate_number_of_letters(text)
    number_of_words = calculate_number_of_words(text)
    index = calculate_Coleman_Liau_index(number_of_sentences, number_of_words, number_of_letters)
    print_reading_level(index)
    

def calculate_number_of_sentences(text):
    number_of_sentences = 0
    for i in range(len(text)):
        if text[i] in ["?", "!", "."]:
            number_of_sentences += 1

    return number_of_sentences
    
    
def calculate_number_of_letters(text):
    number_of_letters = 0
    for c in text:
        for i in range(26):
            if c.lower() == chr(97 + i):
                number_of_letters += 1
    
    return number_of_letters
    
    
def calculate_number_of_words(text):
    number_of_words = 0
    for i in range(len(text)):
        if text[i] == " ":
            number_of_words += 1
    
    return number_of_words + 1
    

def calculate_Coleman_Liau_index(sentences, words, letters):
    return round(0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8)
    

def print_reading_level(index):
    if index < 1:
        return print("Before Grade 1")
    if index >= 16:
        return print("Grade 16+")
    else:
        return print(f"Grade {index}")


if __name__ == "__main__":
    main()