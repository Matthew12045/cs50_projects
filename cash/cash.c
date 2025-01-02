#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    int quaters;
    int dimes;
    int nickels;
    int pennies;

    int calc_quaters(int cents);
    int calc_dimes(int cents);
    int calc_nickels(int cents);
    do
    {
        cents = get_int("Change owned: ");
    }
    while (cents < 0);
    // Calculate how many quarters you should give customer
    // Subtract the value of those quarters from cents
    quaters = calc_quaters(cents);
    cents -= (quaters * 25);

    // Calculate how many dimes you should give customer
    // Subtract the value of those dimes from remaining cents
    dimes = calc_dimes(cents);
    cents -= (dimes * 10);

    // Calculate how many nickels you should give customer
    // Subtract the value of those nickels from remaining cents
    nickels = calc_nickels(cents);
    cents -= (nickels * 5);

    // Calculate how many pennies you should give customer
    // Subtract the value of those pennies from remaining cents
    pennies = cents;

    // Sum the number of quarters, dimes, nickels, and pennies used
    // Print that sum
    int sum = quaters + dimes + nickels + pennies;
    printf("%i\n", sum);
    printf("%i\n", cents);
}

int calc_quaters(int cents)
{
    int quaters = 0;
    while (cents >= 25)
    {
        quaters++;
        cents -= 25;
    }
    return quaters;
}

int calc_dimes(int cents)
{
    int dimes = 0;
    while (cents < 25 && cents >= 10)
    {
        dimes++;
        cents -= 10;
    }
    return dimes;
}

int calc_nickels(int cents)
{
    int nickels = 0;
    while (cents < 10 && cents >= 5)
    {
        nickels++;
        cents -= 5;
    }
    return nickels;
}
