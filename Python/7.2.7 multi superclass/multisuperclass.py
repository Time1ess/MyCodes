__metaclass__=type

class Calculator:
	print 'Calculator'
	def calculate(self,expression):
		self.value=eval(expression)

class Talker:
	print 'Talker'
	def talk(self):
		print 'Hi,my value is ',self.value

class TalkingCalculator(Calculator,Talker):#if a subclass inherit a method from multiple superclass,which means you have two methods that they hava the same name,so you have to pay attention to the order of the inheritence:the superclass inherits early will overwrite the superclass later.So in this case,if Calculator has a method names 'talk',then you should write like this:
	#class TalkingCalculator(Talker,Calculator):pass
	pass

tc=TalkingCalculator()
tc.calculate('1+2*3')
tc.talk()
