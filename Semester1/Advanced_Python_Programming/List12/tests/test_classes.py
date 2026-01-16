from data_access import *
import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))


class TestFriendsDB(unittest.TestCase):
    def setUp(self):
        with Session(engine) as session:
            session.query(Friend).delete()
            session.commit()

    def tearDown(self):
        with Session(engine) as session:
            session.query(Friend).delete()
            session.commit()

    def test_add_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend = session.query(Friend).first()
            self.assertIsNotNone(friend)
            self.assertEqual(friend.name, "Name")

    def test_update_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id
        db_update_friend(
            friend_id,
            "Updated name",
            "updatedemail@gmail.com",
            "987654321")
        with Session(engine) as session:
            friend = session.get(Friend, friend_id)
            self.assertEqual(friend.name, "Updated name")
            self.assertEqual(friend.email, "updatedemail@gmail.com")
            self.assertEqual(friend.phone_number, "987654321")

    def test_delete_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id
        db_delete_friend(friend_id)
        with Session(engine) as session:
            friend = session.get(Friend, friend_id)
            self.assertIsNone(friend)


class TestBooksDB(unittest.TestCase):
    def setUp(self):
        with Session(engine) as session:
            session.query(Book).delete()
            session.commit()

    def tearDown(self):
        with Session(engine) as session:
            session.query(Book).delete()
            session.commit()

    def test_add_book(self):
        db_add_book(2026, "Author 1", "Title 1")
        with Session(engine) as session:
            book = session.query(Book).first()
            self.assertIsNotNone(book)
            self.assertEqual(book.title, "Title 1")

    def test_update_book(self):
        db_add_book(2026, "Author 1", "Title 1")
        with Session(engine) as session:
            book_id = session.query(Book).first().id
        db_update_book(book_id, 2027, "Updated author", "Updated title")
        with Session(engine) as session:
            book = session.get(Book, book_id)
            self.assertEqual(book.year, 2027)
            self.assertEqual(book.author, "Updated author")
            self.assertEqual(book.title, "Updated title")

    def test_delete_book(self):
        db_add_book(2026, "Author 1", "Title 1")
        with Session(engine) as session:
            book_id = session.query(Book).first().id
        db_delete_book(book_id)
        with Session(engine) as session:
            book = session.get(Book, book_id)
            self.assertIsNone(book)


if __name__ == "__main__":
    unittest.main()
