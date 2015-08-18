__metaclass__=type

class FooBar:
	def __init__(self,value=42):
		self.somevar=value

f=FooBar('This is a constructor argument')
print f.somevar
g=FooBar()
print g.somevar
