import re
import math
# Count the number of letters, words, and sentences per text.

# Coleman-Liau index formula:
# 		index = 0.0588 * L - 0.296 * S - 15.8
#  where L is the average number of letters per 100 words in the text, 
#  and S is the average number of sentences per 100 words in the text.
#  regex source for Sentences: https://www.sitepoint.com/community/t/choose-whole-sentences-and-only-whole-sentences-reliably-with-regex/8075


def calculateIndex():

	text = input("Text: ")

	letters = re.findall("[a-zA-Z]", text)
	words = re.findall(r"[\w'-]+", text)
	sentences = re.findall(r'["’]?[A-Z][^.?!]+((?![.?!][’"]?\s["’]?[A-Z][^.?!]).)+[.?!’"]+', text)

	L = (100*len(letters))/len(words)
	S = (100*len(sentences))/len(words)

	index = round(0.0588 * L - 0.296 * S - 15.8)

	if index < 16:
		print('Grade', index)
	else:
		print('Grade 16+')

if __name__ == '__main__':
	calculateIndex()
