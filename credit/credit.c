#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cNum;
    bool isValid;
    int cardType;
    int digits;

    bool checkSum(long cNum);
    int checkDigits(long cNum);
    int checkCCType(long cNum);

    // prompt the user for the credit card number
    do
    {
        cNum = get_long("Number: ");
    }
    while (cNum < 0);

    // check the first two digits of the card for the typr of credit card
    cardType = checkCCType(cNum);

    // check how long is the credit card number
    digits = checkDigits(cNum);

    // do the checksum to check if the card is valid
    isValid = checkSum(cNum);
    // print out the type of the credit card or is the card valid
    if (isValid == true && cardType == 0 && digits == 15)
    {
        printf("AMEX\n");
    }
    else if (isValid == true && cardType == 1 && digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (isValid == true && cardType == 2 && (digits == 13 || digits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checkSum(long cNum)
{
    long number = cNum;
    int digit;
    int sum = 0;
    bool is_second = false;

    while (number > 0)
    {
        digit = number % 10;
        if (is_second)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit - 9;
            }
        }
        sum += digit;
        number /= 10;
        is_second = !is_second;
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int checkCCType(long cNum)
{
    long number = cNum;
    while (number >= 100)
    {
        number /= 10;
    }
    if (number == 34 || number == 37)
    {
        return 0;
    }
    else if (number >= 51 && number <= 55)
    {
        return 1;
    }
    else if (number >= 40 && number <= 50)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

int checkDigits(long cNum)
{
    int digits = 0;
    long num = cNum;
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}
