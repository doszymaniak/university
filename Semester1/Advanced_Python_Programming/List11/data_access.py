import requests
from server import Book, Borrow, Friend, Session, engine

API_URL = "http://localhost:5000"

# BOOK - API
def api_add_book(new_year, new_author, new_title):
    data = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.put(f"{API_URL}/book/", json=data)
    print(res.json())

def api_list_books():
    res = requests.get(f"{API_URL}/book/")
    print(res.json())

def api_update_book(book_id, new_year, new_author, new_title):
    data = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.post(f"{API_URL}/book/{book_id}", json=data)
    print(res.json())

def api_delete_book(book_id):
    res = requests.delete(f"{API_URL}/book/{book_id}")
    print(res.json())

# FRIEND - API
def api_add_friend(new_name, new_email, new_phone_number):
    data = {}
    data["name"] = new_name
    data["email"] = new_email
    data["phone_number"] = new_phone_number
    res = requests.put(f"{API_URL}/friend/", json=data)
    print(res.json())

def api_list_friends():
    res = requests.get(f"{API_URL}/friend/")
    print(res.json())

def api_update_friend(friend_id, new_name, new_email, new_phone_number):
    data = {}
    data["phone_number"] = new_phone_number
    data["name"] = new_name
    data["email"] = new_email
    res = requests.post(f"{API_URL}/friend/{friend_id}", json=data)
    print(res.json())

def api_delete_friend(friend_id):
    res = requests.delete(f"{API_URL}/friend/{friend_id}")
    print(res.json())

# BORROWS - API
def api_borrow_book(book_id, friend_id, borrow_date):
    res = requests.put(f"{API_URL}/borrows/{book_id}/{friend_id}/{borrow_date}")
    print(res.json())

def api_return_book(borrow_id, return_date):
    res = requests.post(f"{API_URL}/borrows/{borrow_id}/{return_date}")
    print(res.json())

def api_list_borrows():
    res = requests.get(f"{API_URL}/borrows/")
    print(res.json())

# BOOK - DB
def db_add_book(new_year, new_author, new_title):
    book = Book(year=new_year, author=new_author, title=new_title)
    with Session(engine) as session:
        session.add(book)
        session.commit()
        print("A new book has been added!")

def db_list_books():
    with Session(engine) as session:
        books = session.query(Book)
        for book in books:
            print(f"{book.id}: {book.author}, {book.title}, {book.year}")

def db_update_book(book_id, new_year, new_author, new_title):
    with Session(engine) as session:
        book = session.get(Book, book_id)
        if not book:
            print("This book does not exist!")
            return
        if new_title:
            book.title = new_title
        if new_year:
            book.year = new_year
        if new_author:
            book.author = new_author
        session.commit()
        print("A book has been updated!")

def db_delete_book(book_id):
    with Session(engine) as session:
        book = session.get(Book, book_id)
        if book:
            session.delete(book)
            session.commit()
            print("A book has been deleted!")
        else:
            print("This book does not exist!")

# FRIEND - DB
def db_add_friend(new_name, new_email, new_phone_number):
    friend = Friend(name=new_name, email=new_email, phone_number=new_phone_number)
    with Session(engine) as session:
        session.add(friend)
        session.commit()
        print("A new friend has been added!")

def db_list_friends():
    with Session(engine) as session:
        friends = session.query(Friend)
        for friend in friends:
            print(f"{friend.id}: {friend.name}, {friend.email}, {friend.phone_number}")

def db_update_friend(friend_id, new_name, new_email, new_phone_number):
    with Session(engine) as session:
        friend = session.get(Friend, friend_id)
        if not friend:
            print("This friend does not exist!")
            return
        if new_name:
            friend.name = new_name
        if new_email:
            friend.email = new_email
        if new_phone_number:
            friend.phone_number = new_phone_number
        session.commit()
        print("A friend has been updated!")

def db_delete_friend(friend_id):
    with Session(engine) as session:
        friend = session.get(Friend, friend_id)
        if friend:
            session.delete(friend)
            session.commit()
            print("A friend has been deleted!")
        else:
            print("This friend does not exist!")

# BORROWS - DB
def db_borrow_book(curr_book_id, curr_friend_id, curr_borrow_date):
    with Session(engine) as session:
        already_borrowed = session.query(Borrow).filter(
            Borrow.book_id == curr_book_id,
            Borrow.return_date == None
        ).first()
        if not already_borrowed:
            borrow = Borrow(
                book_id=curr_book_id,
                friend_id=curr_friend_id,
                borrow_date=curr_borrow_date
            )
            session.add(borrow)
            session.commit()
            print("A new borrow record has been created!")
        else:
            print("This book is already borrowed!")

def db_return_book(curr_borrow_id, curr_return_date):
    with Session(engine) as session:
        borrow_query = session.query(Borrow).filter(
            Borrow.id == curr_borrow_id,
            Borrow.return_date == None
        ).first()
        if borrow_query:
            borrow_query.return_date = curr_return_date
            session.commit()
            print("The book has been returned!")
        else:
            print("This borrow record does not exist!")

def db_list_borrows():
    with Session(engine) as session:
        borrows = session.query(Borrow)
        if borrows.first() == None:
            print("No borrow records found!")
        for borrow in borrows:
            print(f"{borrow.id}: {borrow.friend_id}, {borrow.book_id}, {borrow.borrow_date}, {borrow.return_date}")