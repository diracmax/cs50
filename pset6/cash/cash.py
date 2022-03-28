from cs50 import get_float

while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break

cents = round(dollars * 100)
quarter = 25
dime = 10
nickel = 5
penny = 1
coins = 0

if cents >= quarter:
    quarter_count = int(cents / quarter)
    coins += quarter_count
    cents -= quarter * quarter_count

if cents >= dime:
    dime_count = int(cents / dime)
    coins += dime_count
    cents -= dime * dime_count


if cents >= nickel:
    nickel_count = int(cents / nickel)
    coins += nickel_count
    cents -= nickel * nickel_count

if cents >= penny:
    penny_count = int(cents / penny)
    coins += penny_count
    cents -= penny * penny_count

print(f"{coins}")