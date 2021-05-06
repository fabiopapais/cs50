from cs50 import get_string


def main():
    text = get_string("Text: ")
    text_length = len(text)

    letter_count = 0.0000
    sentence_count = 0.0000
    word_count = 0.0000

    average_letters = 0.000
    average_sentences = 0.000

    for i in range(text_length):

        # find letters
        if text[i].isalpha():
            letter_count += 1

        # find sentences + words
        if text[i] in [".", "!", "?"]:
            sentence_count += 1
            word_count += 1

        # find words
        if (text[i] == " " and text[i - 1] != "."):
            word_count += 1

    average_letters = letter_count *  ( 100 / word_count )
    average_sentences = sentence_count * ( 100 / word_count )

    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8

    readability = round(index)

    if readability >= 16:
        print("Grade 16+")
    elif readability < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {readability}")


main()