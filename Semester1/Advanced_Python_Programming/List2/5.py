import urllib.request

def compression(text):
    compressed = []
    for char in text:
        if len(compressed) == 0 or compressed[-1][0] != char:
            compressed.append((char, 1))
        else:
            last_char, last_count = compressed.pop()
            compressed.append((last_char, last_count + 1))
    return compressed

def decompression(text):
    result = []
    for char, counter in text:
        for i in range(counter):
            result.append(char)
    return ''.join(result)

compressed = compression("Przykladowyyyyy tekst.....")
print(compressed)
decompressed = decompression(compressed)
print(decompressed)

URL = "https://wolnelektury.pl/media/book/txt/homer-iliada.txt"

# Obiekt reprezentujacy odpowiedz serwera, czyli zawartosc pliku tekstowego
response = urllib.request.urlopen(URL)

# Read czyta i zwraca dane w postaci bajtow, decode zamienia na tekst
text = response.read().decode("utf-8")[1000:2000]

# compressed = compression(text)
# print(compressed)
# decompressed = decompression(compressed)
# print(decompressed)