import cs50
import math

# Function to calculate the number of digits in a credit card number


def checkDigits(cNum):
    digits = 0  # Initialize digit counter
    while cNum > 0:  # Loop until the number becomes 0
        cNum /= 10  # Remove the last digit
        cNum = math.trunc(cNum)  # Truncate to ensure it's an integer
        digits += 1  # Increment the digit count
    return digits  # Return the total number of digits

# Function to determine the credit card type based on the starting digits


def checkCCtype(cNum):
    while cNum >= 100:  # Reduce the number to the first two digits
        cNum /= 10
        cNum = math.trunc(cNum)
    if cNum == 34 or cNum == 37:  # AMEX starts with 34 or 37
        return 0
    elif cNum >= 51 and cNum <= 55:  # MASTERCARD starts with 51-55
        return 1
    elif cNum >= 40 and cNum <= 50:  # VISA starts with 4
        return 2
    else:  # If none match, return an invalid type
        return 3

# Function to validate the credit card number using Luhn's algorithm


def checkSum(cNum):
    sum = 0  # Initialize the checksum
    is_second = False  # Flag to indicate every second digit from the right
    while cNum > 0:
        digit = cNum % 10  # Extract the last digit
        if is_second:  # Double every second digit
            digit *= 2
            if digit > 9:  # If the doubled digit is greater than 9, subtract 9
                digit -= 9
        sum += digit  # Add the digit to the checksum
        cNum /= 10  # Remove the last digit
        cNum = math.trunc(cNum)
        is_second = not (is_second)  # Alternate the is_second flag

    if sum % 10:  # If the checksum is not divisible by 10, it's invalid
        return False
    else:  # Otherwise, it's valid
        return True


# Main program to prompt the user for a credit card number
while True:
    cNum = int(input("Number: "))  # Prompt user for input
    if cNum > 0:  # Ensure the number is positive
        break

# Determine card type, digit count, and validity
cardType = checkCCtype(cNum)
digits = checkDigits(cNum)
isValid = checkSum(cNum)

# Check conditions for each card type and print the result
if isValid and cardType == 0 and digits == 15:  # AMEX has 15 digits
    print("AMEX")
elif isValid and cardType == 1 and digits == 16:  # MASTERCARD has 16 digits
    print("MASTERCARD")
elif isValid and cardType == 2 and (digits == 13 or digits == 16):  # VISA has 13 or 16 digits
    print("VISA")
else:  # If none of the conditions match, it's invalid
    print("INVALID")
