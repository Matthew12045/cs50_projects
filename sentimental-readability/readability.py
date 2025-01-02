import cs50
import re


def countWords(text):
    return text.count(" ") + 1


def countLetters(text):
    count = 0
    for i in text:
        if i.isalpha():
            count += 1
    return count


def countSentences(text):
    return text.count(".") + text.count("!") + text.count("?")


text = input("Text: ")

letters = countLetters(text)
words = countWords(text)
sentences = countSentences(text)

L = (letters / words) * 100
S = (sentences / words) * 100
index = round((0.0588 * L) - (0.296 * S) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
