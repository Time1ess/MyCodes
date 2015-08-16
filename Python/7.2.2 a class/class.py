__metaclass__=type

class Person:

	def setName(self,name):
		self.name=name

	def getName(self):
		return self.name

	def greet(self):
		print "Hello,World!I'm %s."%self.name

foo=Person()
bar=Person()
foo.setName('Luke Skywalker')
bar.setName('Anakin Skywalker')
foo.greet()
bar.greet()
