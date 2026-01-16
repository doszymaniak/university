tests:
	python3 -m unittest tests.test_classes -v

pep8: 
	pycodestyle server.py client.py data_access.py tests/test_classes.py

	autopep8 --in-place --aggressive --aggressive tests/test_classes.py
	autopep8 --in-place --aggressive --aggressive server.py
	autopep8 --in-place --aggressive --aggressive data_access.py
	autopep8 --in-place --aggressive --aggressive client.py

pydoc:
	python -m pydoc client
	python -m pydoc data_access
	python -m pydoc server

mypy:
	mypy *.py