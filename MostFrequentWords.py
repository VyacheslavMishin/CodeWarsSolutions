import re


def top_3_words(text):
    appropriate_words_only = re.findall(r"(?:'*[A-Za-z]*'*[A-Za-z]+'*[A-Za-z]*'*)+", text)
    dct_words = {}
    for word in appropriate_words_only:
        word = word.lower()
        try:
            dct_words[word] += 1
        except KeyError:
            dct_words[word] = 1
    answer = []
    for i in range(3):
        try:
            answer.append(max(dct_words, key=lambda k: dct_words[k]))
        except ValueError:
            break
            
        dct_words.pop(answer[-1], 0)

    return answer
