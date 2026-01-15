from __future__ import annotations
from data_access import *
import argparse

parser = argparse.ArgumentParser(description="Lend books to your friends")

parser.add_argument("--use_api", action="store_true", help="Access data via the API")
parser.add_argument("--use_db", action="store_true", help="Access data directly from the database")

parser.add_argument("--add_book", action="store_true", help="Add a new book")
parser.add_argument("--list_books", action="store_true", help="List all books")
parser.add_argument("--update_book", action="store_true", help="Update a book")
parser.add_argument("--delete_book", action="store_true", help="Delete a book")
parser.add_argument("--add_friend", action="store_true", help="Add a new friend")
parser.add_argument("--list_friends", action="store_true", help="List all friends")
parser.add_argument("--update_friend", action="store_true", help="Update a friend")
parser.add_argument("--delete_friend", action="store_true", help="Delete a friend")
parser.add_argument("--borrow_book", action="store_true", help="Borrow a book")
parser.add_argument("--return_book", action="store_true", help="Return a book")
parser.add_argument("--list_borrows", action="store_true", help="List all borrows")

parser.add_argument("--name")
parser.add_argument("--email")
parser.add_argument("--phone_number")
parser.add_argument("--title")
parser.add_argument("--author")
parser.add_argument("--year", type=int)
parser.add_argument("--book_id", type=int)
parser.add_argument("--friend_id", type=int)
parser.add_argument("--borrow_date")
parser.add_argument("--borrow_id")
parser.add_argument("--return_date")

args = parser.parse_args()

if args.add_book:
    if not args.title or not args.author or not args.year:
        print("Three arguments are required!")
    else:
        if args.use_api:
            api_add_book(args.year, args.author, args.title)
        elif args.use_db:
            db_add_book(args.year, args.author, args.title)

if args.list_books:
    if args.use_api:
        api_list_books()
    elif args.use_db:
        db_list_books()

if args.update_book:
    if not args.book_id:
        print("A book id is required!")
    elif args.use_api:
        api_update_book(args.book_id, args.year, args.author, args.title)
    elif args.use_db:
        db_update_book(args.book_id, args.year, args.author, args.title)

if args.delete_book:
    if not args.book_id:
        print("A book id is required!")
    elif args.use_api:
        api_delete_book(args.book_id)
    elif args.use_db:
        db_delete_book(args.book_id)

if args.add_friend:
    if not args.name or not args.email or not args.phone_number:
        print("Three arguments are required!")
    elif args.use_api:
        api_add_friend(args.name, args.email, args.phone_number)
    elif args.use_db:
        db_add_friend(args.name, args.email, args.phone_number)

if args.list_friends:
    if args.use_api:
        api_list_friends()
    elif args.use_db:
        db_list_friends()

if args.update_friend:
    if not args.friend_id:
        print("A friend id is required!")
    elif args.use_api:
        api_update_friend(args.friend_id, args.name, args.email, args.phone_number)
    elif args.use_db:
        db_update_friend(args.friend_id, args.name, args.email, args.phone_number)

if args.delete_friend:
    if not args.friend_id:
        print("A friend id is required!")
    elif args.use_api:
        api_delete_friend(args.friend_id)
    elif args.use_db:
        db_delete_friend(args.friend_id)

if args.borrow_book:
    if not args.book_id or not args.friend_id or not args.borrow_date:
        print("Three arguments are required!")
    elif args.use_api:
        api_borrow_book(args.book_id, args.friend_id, args.borrow_date)
    elif args.use_db:
        db_borrow_book(args.book_id, args.friend_id, args.borrow_date)

if args.return_book:
    if not args.borrow_id or not args.return_date:
        print("Two arguments are required!")
    elif args.use_api:
        api_return_book(args.borrow_id, args.return_date)
    elif args.use_db:
        db_return_book(args.borrow_id, args.return_date)

if args.list_borrows:
    if args.use_api:
        api_list_borrows()
    elif args.use_db:
        db_list_borrows()