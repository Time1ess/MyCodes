__metaclass__=type

class MyClass:

	@staticmethod
	def smeth():
		print 'This is a static method'

	@classmethod
	def cmeth(cls):
		print 'This is a class method of',cls

MyClass.smeth()
MyClass.cmeth()
