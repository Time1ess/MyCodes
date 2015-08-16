class Secretive:
	def __inaccessible(self):
		print "Bet you can't see me..."

	def accessible(self):
		print "The secret message is:"
		self.__inaccessible()

s=Secretive()
s.accessible()#access private method through public method
s._Secretive__inaccessible()#the way Python using to avoid user to access private method
s.__inaccessible()#tring to access private method,error occurred

