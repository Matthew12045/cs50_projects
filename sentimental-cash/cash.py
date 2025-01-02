import cs50

while True:
    cents = cs50.get_float("Change owned: ") * 100
    if cents > 0:
        break


def calc_quaters(cents):
    quaters = 0
    while cents >= 25:
        quaters += 1
        cents -= 25
    return quaters


def calc_dimes(cents):
    dimes = 0
    while cents < 25 and cents >= 10:
        dimes += 1
        cents -= 10
    return dimes


def calc_nickels(cents):
    nickels = 0
    while cents < 10 and cents >= 5:
        nickels += 1
        cents -= 5
    return nickels


quaters = calc_quaters(cents)
cents -= (quaters * 25)

dimes = calc_dimes(cents)
cents -= (dimes * 10)

nickels = calc_nickels(cents)
cents -= (nickels * 5)

pennies = cents

sum = quaters + dimes + nickels + pennies

print(sum)
