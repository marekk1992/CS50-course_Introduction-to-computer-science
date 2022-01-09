from cs50 import get_float


def main():
    while True:
        change_owed_in_dollars = get_float("Change owed: ")
        if change_owed_in_dollars >= 0:
            break
    
    change_owed_in_cents = int(change_owed_in_dollars * 100)
    amount_of_coins = calculate_amount_of_coins(change_owed_in_cents)
    print(amount_of_coins)


def calculate_amount_of_coins(change_owed):
    amount_of_coins = int(change_owed / 25)
    amount_of_coins += int(change_owed % 25 / 10)
    amount_of_coins += int(change_owed % 25 % 10 / 5)
    amount_of_coins += int(change_owed % 25 % 10 % 5 / 1)
    
    return amount_of_coins
    

if __name__ == "__main__":
    main()