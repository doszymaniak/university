from __future__ import annotations
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy import Integer, ForeignKey, String, create_engine
from sqlalchemy.orm import relationship, mapped_column, Mapped, validates, Session
from typing import List
import re
import argparse
import json
import os

class Base(DeclarativeBase):
    pass

class Borrow(Base):
    __tablename__ = "Borrows"
    id = mapped_column(Integer, primary_key=True)
    book_id = mapped_column(Integer, ForeignKey("Books.id"))
    friend_id = mapped_column(Integer, ForeignKey("Friends.id"))
    borrow_date = mapped_column(String)
    return_date = mapped_column(String, nullable=True)
    @validates("borrow_date", "return_date")
    def validate_date(self, key, date):
        pattern = r"^\d{2}-\d{2}-\d{4}$"
        if date is not None and not re.match(pattern, date):
            raise ValueError("The provided date is invalid!")
        return date
    friend: Mapped["Friend"] = relationship("Friend", back_populates="borrows")
    book: Mapped["Book"] = relationship("Book", back_populates="borrows")

class Book(Base):
    __tablename__ = "Books"
    id = mapped_column(Integer, primary_key=True)
    author = mapped_column(String)
    year = mapped_column(Integer)
    title = mapped_column(String)
    @validates("year")
    def validate_year(self, key, year):
        if year < 0:
            raise ValueError("Year must be greater than zero!")
        return year
    borrows: Mapped[List["Borrow"]] = relationship("Borrow", back_populates="book")
    
class Friend(Base):
    __tablename__ = "Friends"
    id = mapped_column(Integer, primary_key=True)
    name = mapped_column(String)
    email = mapped_column(String)
    phone_number = mapped_column(String)
    @validates("email")
    def validate_email(self, key, email):
        if '@' not in email:
            raise ValueError("The provided email address is invalid!")
        return email
    borrows: Mapped[List["Borrow"]] = relationship("Borrow", back_populates="friend")

parser = argparse.ArgumentParser(description="Lend books to your friends")

parser.add_argument("--add_friend", action="store_true", help="Add a new friend")
parser.add_argument("--list_friends", action="store_true", help="List all friends")
parser.add_argument("--find_friend", action="store_true", help="Find a friend")
parser.add_argument("--add_book", action="store_true", help="Add a new book")
parser.add_argument("--list_books", action="store_true", help="List all books")
parser.add_argument("--find_book", action="store_true", help="Find a book")
parser.add_argument("--borrow_book", action="store_true", help="Borrow a book")
parser.add_argument("--return_book", action="store_true", help="Return a book")
parser.add_argument("--list_borrows", action="store_true", help="List all borrows")

parser.add_argument("--name")
parser.add_argument("--email")
parser.add_argument("--phone")
parser.add_argument("--title")
parser.add_argument("--author")
parser.add_argument("--year", type=int)
parser.add_argument("--book_id", type=int)
parser.add_argument("--friend_id", type=int)
parser.add_argument("--borrow_date")
parser.add_argument("--borrow_id")
parser.add_argument("--return_date")

args = parser.parse_args()

base_exists = os.path.exists("library.db")
engine = create_engine("sqlite:///library.db")
Base.metadata.create_all(engine)

if not base_exists:
    with open("library.json", "r") as f:
        data = json.load(f)
        with Session(engine) as session:
            for b in data.get("books", []):
                book = Book(id=b["id"], title=b["title"], author=b["author"], year=b["year"])
                session.add(book)
                session.commit()
            for fr in data.get("friends", []):
                friend = Friend(id=fr["id"], name=fr["name"], email=fr["email"], phone_number=fr["phone_number"])
                session.add(friend)
                session.commit()
            for br in data.get("borrows", []):
                borrow = Borrow(id=br["id"], book_id=br["book_id"], friend_id=br["friend_id"], 
                    borrow_date=br["borrow_date"], return_date=br["return_date"])
                session.add(borrow)
                session.commit()

with Session(engine) as session:
    if args.add_friend:
        if args.name and args.email and args.phone:
            friend = Friend(name=args.name, email=args.email, phone_number=args.phone)
            session.add(friend)
            session.commit()
            print("A new friend has been added!")
        else:
            print("Three arguments are required!")
    
    if args.list_friends:
        friends = session.query(Friend)
        if friends.first() == None:
            print("No friends found!")
        for friend in friends:
            print(f"{friend.id}: {friend.name}, {friend.email}, {friend.phone_number}")

    if args.find_friend:
        query = session.query(Friend)
        if args.name:
            query = query.filter(Friend.name.like(args.name))
        if args.email:
            query = query.filter(Friend.name.like(args.email))
        if args.phone:
            query = query.filter(Friend.name.like(args.phone))
        if query.first() == None:
            print("No matching friends found!")
        for friend in query:
            print(f"{friend.id}: {friend.name}, {friend.email}, {friend.phone_number}")
    
    if args.add_book:
        if args.author and args.title and args.year:
            book = Book(author=args.author, title=args.title, year=args.year)
            session.add(book)
            session.commit()
            print("A new book has been added!")
        else:
            print("Three arguments are required!")

    if args.list_books:
        books = session.query(Book)
        if books.first() == None:
            print("No books found!")
        for book in books:
            print(f"{book.id}: {book.author}, {book.title}, {book.year}")

    if args.find_book:
        query = session.query(Book)
        if args.author:
            query = query.filter(Book.author.like(args.author))
        if args.title:
            query = query.filter(Book.title.like(args.title))
        if args.year:
            query = query.filter(Book.year.like(args.year))
        if query.first() == None:
            print("No matching books found!")
        for book in query:
            print(f"{book.id}: {book.author}, {book.title}, {book.year}")
    
    if args.borrow_book:
        if args.book_id and args.friend_id and args.borrow_date:
            already_borrowed = session.query(Borrow).filter(
                Borrow.book_id == args.book_id,
                Borrow.return_date == None
            ).first()
            if not already_borrowed:
                borrow = Borrow(
                    book_id=args.book_id,
                    friend_id=args.friend_id,
                    borrow_date=args.borrow_date
                )
                session.add(borrow)
                session.commit()
                print("A new borrow record has been created!")
            else:
                print("This book is already borrowed!")

    if args.return_book:
        if args.borrow_id and args.return_date:
            borrow_query = session.query(Borrow).filter(
                Borrow.id == args.borrow_id,
                Borrow.return_date == None
            ).first()
            if borrow_query:
                borrow_query.return_date = args.return_date
                session.commit()
                print("The book has been returned!")
            else:
                print("This borrow record does not exist!")
    
    if args.list_borrows:
        borrows = session.query(Borrow)
        if borrows.first() == None:
            print("No borrow records found!")
        for borrow in borrows:
            print(f"{borrow.id}: {borrow.friend_id}, {borrow.book_id}, {borrow.borrow_date}, {borrow.return_date}")