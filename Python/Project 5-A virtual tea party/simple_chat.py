from asyncore import dispatcher
from asynchat import async_chat
import asyncore,socket

PORT=5005
NAME='TestChat'

class ChatSession(async_chat):

	def __init__(self,server,sock):
		async_chat.__init__(self,sock)
		self.set_terminator("\r\n")
		self.server=server
		self.data=[]
		self.push('Welcome to %s\r\n' % self.server.name)
	
	def collect_incoming_data(self,data):
		self.data.append(data)

	def found_terminator(self):
		line=''.join(self.data)
		self.data=[]
		self.server.broadcast(line)

class ChatServer(dispatcher):

	def __init__(self,port,name):
		dispatcher.__init__(self)
		self.create_socket(socket.AF_INET,socket.SOCK_STREAM)
		self.set_reuse_addr()
		self.bind(('',PORT))
		self.listen(5)
		self.name=name
		self.sessions=[]

	def disconnect(self,session):
		print 'Disconnect Addr:%s Port:%s' %(session.addr[0],
				session.addr[1])
		self.sessions.remove(session)

	def broadcast(self,line):
		for session in self.sessions:
			session.push(line+'\r\n')

	def handle_accept(self):
		conn,addr=self.accept()
		print 'Connect Address:%s Port:%s' % (addr[0],addr[1])
		self.sessions.append(ChatSession(self,conn))


if __name__=='__main__':
	s=ChatServer(PORT,NAME)
	try:
		asyncore.loop()
	except KeyboardInterrupt:
		print
