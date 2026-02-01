import os

current_user = None

STATE_FILE = "current_user.txt"


def get_user():
    try:
        user = open(STATE_FILE).read().strip()
        return user if user else None
    except FileNotFoundError:
        return None


def set_user(user):
    open(STATE_FILE, "w").write(user)


def clear_user():
    open(STATE_FILE, "w").write("")
