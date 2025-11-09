import requests
import bs4
import re

texts = {}

def url_to_text(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None 
    soup = bs4.BeautifulSoup(response.text, 'html.parser')
    return soup.get_text(separator=' ').lower()

def generate_dictionary(list_of_urls):
    word_count = {}
    for curr_url in list_of_urls:
        text = url_to_text(curr_url)
        if text is None:
            continue
        text = re.findall(r"[a-zA-Z]+", text) 
        texts[curr_url] = text
        for word in text:
            word_count[word] = word_count.get(word, 0) + 1
    return word_count

def most_popular_word(word_count):
    if len(word_count) == 0:
        return None
    return max(word_count, key=word_count.get)

def search_word(word, list_of_urls):
    urls_with_word = []
    for curr_url in list_of_urls:
        if curr_url in texts and word in texts[curr_url]:
            urls_with_word.append(curr_url)
    return urls_with_word


list_of_urls = ["https://www.nytimes.com/international/",
                "https://www.nbcnews.com/",
                "https://www.bbc.com/",
                "https://www.nasa.gov/"]

word_count_dict = generate_dictionary(list_of_urls) 

most_popular = most_popular_word(word_count_dict)

urls_with_word = search_word(most_popular, list_of_urls)

print(f"Slowo '{most_popular}' wystepuje na tych stronach:")
for cnt, url in enumerate(urls_with_word, 1):
    print(f"{cnt}) {url} - {texts[url].count(most_popular)} razy")