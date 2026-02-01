from __future__ import annotations
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy import Integer, ForeignKey, String, create_engine
from sqlalchemy.orm import relationship, mapped_column, Mapped, validates, Session
from typing import List
from flask import Flask, request, jsonify
import re


class Base(DeclarativeBase):
    """
    A base class for all models
    """
    pass


class Borrow(Base):
    """
    A class representing a borrow record
    """
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
    """
    A class representing a book borrowed by a friend
    """
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
    borrows: Mapped[List["Borrow"]] = relationship(
        "Borrow", back_populates="book")


class Friend(Base):
    """
    A class representing a friend who can borrow books
    """
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
    borrows: Mapped[List["Borrow"]] = relationship(
        "Borrow", back_populates="friend")


engine = create_engine("sqlite:///library.db")
Base.metadata.create_all(engine)

app = Flask(__name__)


@app.route('/book/', methods=["PUT"])
def add_book():
    """
    Adds a new book via the API
    """
    with Session(engine) as session:
        data = request.get_json()
        new_title = data.get("title")
        new_author = data.get("author")
        new_year = data.get("year")
        book = Book(author=new_author, title=new_title, year=new_year)
        session.add(book)
        session.commit()
        return jsonify({'msg': 'A new book has been added!'})


@app.route('/book/', methods=["GET"])
def list_books():
    """
    Lists all books via the API
    """
    with Session(engine) as session:
        books = session.query(Book)
        res = [{"id": b.id,
                "author": b.author,
                "title": b.title,
                "year": b.year} for b in books]
        return jsonify(res)


@app.route('/book/<int:book_id>', methods=["POST"])
def update_book(book_id: int):
    """
    Updates a book with a given id via the API
    """
    with Session(engine) as session:
        curr_book = session.get(Book, book_id)
        if not curr_book:
            return jsonify({'msg': "This book does not exist!"})
        data = request.get_json()
        new_title = data.get("title")
        new_author = data.get("author")
        new_year = data.get("year")
        if new_title:
            curr_book.title = new_title
        if new_author:
            curr_book.author = new_author
        if new_year:
            curr_book.year = new_year
        session.commit()
        return jsonify({'msg': "A book has been updated!"})


@app.route('/book/<int:book_id>', methods=["DELETE"])
def delete_book(book_id: int):
    """
    Deletes a book with a given id via the API
    """
    with Session(engine) as session:
        curr_book = session.get(Book, book_id)
        if curr_book:
            session.delete(curr_book)
            session.commit()
            return jsonify({'msg': 'A book has been deleted!'})
        else:
            return jsonify({'msg': 'This book does not exist!'})


@app.route('/friend/', methods=["PUT"])
def add_friend():
    """
    Adds a new friend via the API
    """
    with Session(engine) as session:
        data = request.get_json()
        new_name = data.get("name")
        new_email = data.get("email")
        new_phone_number = data.get("phone_number")
        friend = Friend(
            phone_number=new_phone_number,
            email=new_email,
            name=new_name)
        session.add(friend)
        session.commit()
        return jsonify({'msg': 'A new friend has been added!'})


@app.route('/friend/', methods=["GET"])
def list_friends():
    """
    Lists all friends via the API
    """
    with Session(engine) as session:
        friends = session.query(Friend)
        res = [{"id": f.id, "name": f.name, "email": f.email,
                "phone_number": f.phone_number} for f in friends]
        return jsonify(res)


@app.route('/friend/<int:friend_id>', methods=["POST"])
def update_friend(friend_id: int):
    """
    Updates a friend via the API
    """
    with Session(engine) as session:
        curr_friend = session.get(Friend, friend_id)
        if not curr_friend:
            return jsonify({'msg': "This friend does not exist!"})
        data = request.get_json()
        new_name = data.get("name")
        new_email = data.get("email")
        new_phone_number = data.get("phone_number")
        if new_name:
            curr_friend.name = new_name
        if new_email:
            curr_friend.email = new_email
        if new_phone_number:
            curr_friend.phone_number = new_phone_number
        session.commit()
        return jsonify({'msg': "A friend has been updated!"})


@app.route('/friend/<int:friend_id>', methods=["DELETE"])
def delete_friend(friend_id: int):
    """
    Deletes a friend via the API
    """
    with Session(engine) as session:
        curr_friend = session.get(Friend, friend_id)
        if curr_friend:
            session.delete(curr_friend)
            session.commit()
            return jsonify({'msg': 'A friend has been deleted!'})
        else:
            return jsonify({'msg': 'This friend does not exist!'})


@app.route('/borrows/<int:curr_book_id>/<int:curr_friend_id>/<string:curr_borrow_date>',
           methods=["PUT"])
def borrow_book(curr_book_id: int, curr_friend_id: int, curr_borrow_date: str):
    """
    Creates a new borrow record via the API
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
            return jsonify({'msg': 'A new borrow record has been created!'})
        else:
            return jsonify({'msg': 'This book is already borrowed!'})


@app.route('/borrows/<int:curr_borrow_id>/<string:curr_return_date>',
           methods=["POST"])
def return_book(curr_borrow_id: int, curr_return_date: str):
    """
    Returns a book with a given id via the API
    """
    with Session(engine) as session:
        borrow_query = session.query(Borrow).filter(
            Borrow.id == curr_borrow_id,
            Borrow.return_date.is_(None)
        ).first()
        if borrow_query:
            borrow_query.return_date = curr_return_date
            session.commit()
            return jsonify({'msg': 'The book has been returned!'})
        else:
            return jsonify({'msg': 'This borrow record does not exist!'})


@app.route('/borrows/', methods=["GET"])
def list_borrows():
    """
    Lists all borrow records via the API
    """
    with Session(engine) as session:
        borrows = session.query(Borrow)
        if borrows.first() is None:
            return jsonify({'msg': 'No borrow records found!'})
        res = [{"id": b.id,
                "friend_id": b.friend_id,
                "book_id": b.book_id,
                "borrow_date": b.borrow_date,
                "return_date": b.return_date} for b in borrows]
        return jsonify(res)


if __name__ == "__main__":
    app.run(debug=True)
