def square(x):
	'''
	Squares a number and returns the result.

	>>> square(2)
	4
	>>> square(3)
	9
	'''
	return x*x

import sys,doctest,my_math
sys.path.append('D:/MyCodes/Python')
doctest.testmod(my_math)
