from test_classes import *
import unittest

def run_tests():
    s1 = unittest.TestLoader().loadTestsFromTestCase(TestFriendsDB)
    s2 = unittest.TestLoader().loadTestsFromTestCase(TestBooksDB)
    alltests = unittest.TestSuite([s1, s2])
    unittest.TextTestRunner(verbosity=3).run(alltests)