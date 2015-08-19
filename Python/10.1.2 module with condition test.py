#hello4.py

def hello():
	print "Hello,world!"

def test():
	hello()

if __name__=='__main__':
	test()

#module performance

#As a module
#>>> import hello4
#>>> hello4.hello()
#Hello,world!

#As a program
#print 'Hello,world'
#it all depends on variable '__name__'
