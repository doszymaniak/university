from test_classes import *
import unittest


def run_tests():
    s1 = unittest.TestLoader().loadTestsFromTestCase(TestLogin)
    alltests = unittest.TestSuite(s1)
    unittest.TextTestRunner(verbosity=3).run(alltests)
