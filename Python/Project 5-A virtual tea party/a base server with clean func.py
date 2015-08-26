from asyncore import dispatcher
import asyncore,socket

PORT=5005

class ChatServer(dispatcher):

	def __init__(self,port):
		dispatcher.__init__(self)
		self.create_socket(socket.AF_INET,socket.SOCK_STREAM)
		self.set_reuse_addr()
		self.bind(('',PORT))
		self.listen(5)

	def handle_accept(self):
		conn,addr=self.accept()
		print 'Connection attempt from',addr[0]


if __name__=='__main__':
	s=ChatServer(PORT)
	try:
		asyncore.loop()
	except KeyboardInterrupt:
		pass
