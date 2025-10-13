import string

def preprocess(text):
    result = ""
    for ch in text:
        if ch.lower().isalnum():
            result += ch.lower()
    return result

def is_palindrome(text):
    processed = preprocess(text)
    return processed == processed[::-1]

print(is_palindrome("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrome("Míč omočím."))
print(is_palindrome("kajak"))