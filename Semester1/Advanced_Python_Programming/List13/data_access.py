import requests
from server import Book, Borrow, Friend, Session, engine
from typing import Any
import shelve
import functools
import state

API_URL = "http://localhost:5000"


def cache_function(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        key = (func.__name__, args, tuple(sorted(kwargs.items())))
        db = shelve.open("/tmp/query.cache")
        key = str(hash(key))
        if key in db:
            res = db[key]
            print("Cache!")
            print(res)
            return res
        res = func(*args, **kwargs)
        db[key] = res
        db.sync()
        return res
    return wrapper


def clear_cache(func, *args, **kwargs):
    key = (func.__name__, args, tuple(sorted(kwargs.items())))
    key = str(hash(key))
    db = shelve.open("/tmp/query.cache")
    if key in db:
        del db[key]
        db.sync()
        print("Cache cleared!")


def requires_login(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        if state.get_user() is None:
            print("This option is available to logged in users!")
            return
        return func(*args, **kwargs)
    return wrapper


def api_add_book(new_year: int, new_author: str, new_title: str):
    """
    Creates a request to add a book via the API
    Args: new_year, new_author, new_title
    """
    data: dict[str, Any] = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.put(f"{API_URL}/book/", json=data)
    print(res.json())
    clear_cache(api_list_books)


@cache_function
def api_list_books():
    """
    Creates a request to list all books via the API
    """
    res = requests.get(f"{API_URL}/book/")
    print(res.json())
    return res.json()


def api_update_book(
        book_id: int,
        new_year: int,
        new_author: str,
        new_title: str):
    """
    Creates a request to update a book with a given id via the API
    Args: book_id, new_year, new_author, new_title
    """
    data: dict[str, Any] = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.post(f"{API_URL}/book/{book_id}", json=data)
    print(res.json())
    clear_cache(api_list_books)


def api_delete_book(book_id: int):
    """
    Creates a request to delete a book with a given id via the API
    Args: book_id
    """
    res = requests.delete(f"{API_URL}/book/{book_id}")
    print(res.json())


@requires_login
def api_add_friend(new_name: str, new_email: str, new_phone_number: str):
    """
    Creates a request to add a friend via the API
    Args: new_name, new_email, new_phone_number
    """
    data = {}
    data["name"] = new_name
    data["email"] = new_email
    data["phone_number"] = new_phone_number
    res = requests.put(f"{API_URL}/friend/", json=data)
    print(res.json())


def api_list_friends():
    """
    Creates a request to list all friends via the API
    """
    res = requests.get(f"{API_URL}/friend/")
    print(res.json())


@requires_login
def api_update_friend(
        friend_id: int,
        new_name: str,
        new_email: str,
        new_phone_number: str):
    """
    Creates a request to update a friend via the API
    Args: friend_id, new_name, new_email, new_phone_number
    """
    data = {}
    data["phone_number"] = new_phone_number
    data["name"] = new_name
    data["email"] = new_email
    res = requests.post(f"{API_URL}/friend/{friend_id}", json=data)
    print(res.json())


@requires_login
def api_delete_friend(friend_id: int):
    """
    Creates a request to delete a friend with a given id via the API
    Args: friend_id
    """
    res = requests.delete(f"{API_URL}/friend/{friend_id}")
    print(res.json())


def api_borrow_book(book_id: int, friend_id: int, borrow_date: str):
    """
    Creates a request to create a new borrow record
    Args: book_id, friend_id, borrow_date
    """
    res = requests.put(
        f"{API_URL}/borrows/{book_id}/{friend_id}/{borrow_date}")
    print(res.json())


def api_return_book(borrow_id: int, return_date: str):
    """
    Creates a request to return a book
    Args: borrow_id, return_date
    """
    res = requests.post(f"{API_URL}/borrows/{borrow_id}/{return_date}")
    print(res.json())


def api_list_borrows():
    """
    Creates a request to list all borrow records
    """
    res = requests.get(f"{API_URL}/borrows/")
    print(res.json())


def db_add_book(new_year: int, new_author: str, new_title: str):
    """
    Adds a new book to the database
    Args: new_year, new_author, new_title
    """
    book = Book(year=new_year, author=new_author, title=new_title)
    with Session(engine) as session:
        session.add(book)
        session.commit()
        print("A new book has been added!")


def db_list_books():
    """
    Lists all books from the database
    """
    with Session(engine) as session:
        books = session.query(Book)
        for book in books:
            print(f"{book.id}: {book.author}, {book.title}, {book.year}")


def db_update_book(
        book_id: int,
        new_year: int,
        new_author: str,
        new_title: str):
    """
    Updates a book with a given id in the database
    Args: book_id, new_year, new_author, new_title
    """
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


def db_delete_book(book_id: int):
    """
    Deletes a book with a given id from the database
    Args: book_id
    """
    with Session(engine) as session:
        book = session.get(Book, book_id)
        if book:
            session.delete(book)
            session.commit()
            print("A book has been deleted!")
        else:
            print("This book does not exist!")


def db_add_friend(new_name: str, new_email: str, new_phone_number: str):
    """
    Adds a new friend to the database
    Args: new_name, new_email, new_phone_number
    """
    friend = Friend(
        name=new_name,
        email=new_email,
        phone_number=new_phone_number)
    with Session(engine) as session:
        session.add(friend)
        session.commit()
        print("A new friend has been added!")


def db_list_friends():
    """
    Lists all friends from the database
    """
    with Session(engine) as session:
        friends = session.query(Friend)
        for friend in friends:
            print(f"{friend.id}: {friend.name}, "
                  f"{friend.email}, {friend.phone_number}")


def db_update_friend(
        friend_id: int,
        new_name: str,
        new_email: str,
        new_phone_number: str):
    """
    Updates a friend with a given id in the database
    Args: friend_id, new_name, new_email, new_phone_number
    """
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


def db_delete_friend(friend_id: int):
    """
    Deletes a friend with a given id from the database
    Args: friend_id
    """
    with Session(engine) as session:
        friend = session.get(Friend, friend_id)
        if friend:
            session.delete(friend)
            session.commit()
            print("A friend has been deleted!")
        else:
            print("This friend does not exist!")


def db_borrow_book(
        curr_book_id: int,
        curr_friend_id: int,
        curr_borrow_date: str):
    """
    Creates a new borrow record in the database
    Args: curr_book_id, curr_friend_id, curr_borrow_date
    """
    with Session(engine) as session:
        already_borrowed = session.query(Borrow).filter(
            Borrow.book_id == curr_book_id,
            Borrow.return_date.is_(None)
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


def db_return_book(curr_borrow_id: int, curr_return_date: str):
    """
    Returns a book in the database
    Args: curr_borrow_id, curr_return_date
    """
    with Session(engine) as session:
        borrow_query = session.query(Borrow).filter(
            Borrow.id == curr_borrow_id,
            Borrow.return_date.is_(None)
        ).first()
        if borrow_query:
            borrow_query.return_date = curr_return_date
            session.commit()
            print("The book has been returned!")
        else:
            print("This borrow record does not exist!")


def db_list_borrows():
    """
    Lists all borrow records in the database
    """
    with Session(engine) as session:
        borrows = session.query(Borrow)
        if borrows.first() is None:
            print("No borrow records found!")
        for borrow in borrows:
            print(f"{borrow.id}: {borrow.friend_id}, {borrow.book_id}, "
                  f"{borrow.borrow_date}, {borrow.return_date}")
