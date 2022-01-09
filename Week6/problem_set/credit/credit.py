from cs50 import get_int


def main():
    card_number = get_int("Number: ")
    converted_card_number = str(card_number)
    
    if len(converted_card_number) in [13, 15, 16]:
        checksum = calculate_checksum(card_number)
        if checksum % 10 != 0:
            print("INVALID")
        card_type = str(get_card_type(converted_card_number))
        print(card_type)
    else:
        print("INVALID")


def calculate_checksum(card_number):
    divider1 = 10
    divider2 = 1
    sum1 = 0
    sum2 = 0
    while int(card_number / divider1) or int(card_number / divider2) > 0:
        number1 = (int(card_number / divider1) % 10) * 2
        if number1 >= 10:
            number1 = int(number1 / 10) + int(number1 % 10)
        number2 = int(card_number / divider2) % 10
        divider1 *= 100
        divider2 *= 100
        sum1 += number1
        sum2 += number2
    sum = sum1 + sum2
    
    return sum
    

def get_card_type(converted_card_number):
    if int(converted_card_number[0]) == 3 and \
            int(converted_card_number[1]) == 7 or 4 and \
            len(converted_card_number) == 15:
        return "AMEX"
                    
    if int(converted_card_number[0]) == 4 and len(converted_card_number) == (16 or 13):
        return "VISA"
                
    if int(converted_card_number[0]) == 5 and \
            int(converted_card_number[1]) == 1 or 2 or 3 or 4 or 5 and \
            len(converted_card_number) == 16:
        return "MASTERCARD"
    

if __name__ == "__main__":
    main()