from cs50 import get_int


number = get_int("Number: ")

odd_total = 0
even_total_double = 0

n = number
count = 0
upper_two_digits = 0

while n > 0:
    digits = n % 10
    if count % 2 == 0:
        odd_total += digits
    else:
        j = 2 * digits
        if j >= 10:
            k = j % 10
            j = int((j - k) / 10)
            even_total_double += (j + k)
        else:
            even_total_double += j

    n = int((n - digits) / 10)
    count += 1

    if n < 100 and n > 9:
        upper_two_digits = n


total = even_total_double + odd_total

if total % 10 == 0:
    upper_number = 0
    if upper_two_digits == 34 or upper_two_digits == 37:
        if count == 15:
            print("AMEX")
        else:
            print("INVALID")
        upper_number += 1
    if upper_two_digits - (upper_two_digits % 10) == 40:
        if count == 13 or count == 16:
            print("VISA")
        else:
            print("INVALID")
        upper_number += 1
    if upper_two_digits == 51 or upper_two_digits == 52 or upper_two_digits == 53 or upper_two_digits == 54 or upper_two_digits == 55:
        if count == 16:
            print("MASTERCARD")
        else:
            print("INVALID")
        upper_number += 1
    if upper_number == 0:
        print("INVALID")
else:
    print("INVALID")

