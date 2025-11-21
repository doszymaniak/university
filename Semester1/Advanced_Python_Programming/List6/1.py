# We run the 'url_to_text' function in separate threads because fetching URLs is slow
# when performed sequentially
# Threads allow us to perform these downloads concurrently
# Modifying a shared dictionary from multiple threads is dangerous because
# race conditions may occur and data may be lost or overwritten
# A Lock ensures that only one thread writes to the shared data structure at a time
import requests
import bs4
import re
import threading

texts = {}
word_count = {}
lock = threading.Lock()

def process_url(url):
    global word_count
    global texts
    text = url_to_text(url)
    if text is None: 
        return
    text = re.findall(r"[a-zA-Z]+", text) 
    lock.acquire()
    try:
        texts[url] = text
        for word in text:
            word_count[word] = word_count.get(word, 0) + 1
    finally:
        lock.release()
        
def url_to_text(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None 
    soup = bs4.BeautifulSoup(response.text, 'html.parser')
    return soup.get_text(separator=' ').lower()

# Creates a list of threads
# Starts each thread, waits for all of them to finish and returns the final dictionary
def generate_dictionary(list_of_urls):
    threads = []
    for url in list_of_urls:
        # 'args' must be a tuple
        t = threading.Thread(target=process_url, args=(url, ))
        t.start()
        threads.append(t)
    for t in threads:
        t.join()
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

print(f"The word '{most_popular}' was found on the following sites:")
for cnt, url in enumerate(urls_with_word, 1):
    print(f"{cnt}) {url} - {texts[url].count(most_popular)} times")