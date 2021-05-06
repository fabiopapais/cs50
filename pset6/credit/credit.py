from cs50 import get_int


def main():
    credit_card = get_int("Number: ")

    sumLastDigit = check_sum(credit_card)

    if sumLastDigit == 0:
        card_prefix = str(credit_card)[slice(2)]

        # card recognizing
        if length(credit_card) == 16:
            if int(card_prefix[0]) == 4:
                print("VISA")
            elif card_prefix == 51 or 52 or 53 or 54 or 55:
                print("MASTERCARD")
            else:
                print("INVALID")

        elif length(credit_card) == 15:
            if card_prefix == 34 or 37:
                print("AMEX")
            else:
                print("INVALID")

        elif length(credit_card) == 13:
            if int(card_prefix[0]) == 4:
                print("VISA")
            else:
                print("INVALID")

        else:
            print("INVALID")
    else:
        print("INVALID")

# support function that returns the sum results
def check_sum(number):
    evens = 0
    odds = 0
    i = 0

    while number:
        digit = int(number % 10) # this operations gives you the last digit
        number = int(number / 10)

        if i % 2 == 0:
            evens += digit
        else:
            oddDigits = digit * 2
            if oddDigits >= 10:
                oddDigit = 0
                while oddDigits:
                    oddDigit = int(oddDigits % 10)
                    oddDigits = int(oddDigits / 10)
                    odds += oddDigit
            else:
                odds += oddDigits
        i += 1

    number_sum = evens + odds
    return number_sum % 10 # this will give the last number faster

# support function to get the length
def length(number):
    return len(str(number))


main()
