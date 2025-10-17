import random
import urllib.request

def sentence_simplify(text, word_len, word_count):
    text_split = text.split()
    new_text = []
    for word in text_split:
        if (len(word) <= word_len):
            new_text.append(word)
    while (len(new_text) > word_count):
        random_idx = random.randint(0, len(new_text) - 1)
        new_text.pop(random_idx)
    return ' '.join(new_text)

text = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."
print(sentence_simplify(text, 10, 5))

URL = "https://wolnelektury.pl/media/book/txt/homer-iliada.txt"

# Obiekt reprezentujacy odpowiedz serwera, czyli zawartosc pliku tekstowego
response = urllib.request.urlopen(URL)

# Read czyta i zwraca dane w postaci bajtow, decode zamienia na tekst
text = response.read().decode("utf-8")[1000:2000]
print(sentence_simplify(text, 10, 50))