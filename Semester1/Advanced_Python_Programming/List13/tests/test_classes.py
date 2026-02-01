import state
from data_access import *
import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))


class TestLogin(unittest.TestCase):
    def setUp(self):
        state.set_user("")

    def tearDown(self):
        state.set_user("")

    def test_add_friend_requires_login(self):
        result = api_add_friend("Name", "email@example.com", "123456789")
        self.assertIsNone(result)

    def test_update_friend_requires_login(self):
        result = api_update_friend(
            1, "New Name", "newemail@example.com", "987654321")
        self.assertIsNone(result)

    def test_delete_friend_requires_login(self):
        result = api_delete_friend(1)
        self.assertIsNone(result)

    def test_add_friend_with_login(self):
        state.set_user("jan")
        api_add_friend("Name", "email@example.com", "123456789")
        self.assertEqual(state.get_user(), "jan")

    def test_delete_friend_with_login(self):
        state.set_user("jan")
        api_delete_friend(1)
        self.assertEqual(state.get_user(), "jan")


if __name__ == "__main__":
    unittest.main()
