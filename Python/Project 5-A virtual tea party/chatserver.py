#coding=UTF-8
__metaclass__=type
from asyncore import dispatcher
from asynchat import async_chat
import socket,asyncore

PORT=5005
NAME='David\' Chat Room'

class EndSession(Exception):
	pass

class CommandHandler:
	"""
	类似于标准库中cmd.Cmd的简单命令处理程序
	"""

	def unknown(self,session,cmd):
		'响应未知命令'
		session.push('Unkown command:%s\r\n' % cmd)

	def handle(self,session,line):
		'处理从给定的会话中接收到的行'
		if not line.strip():
			return
		#分离命令:
		parts=line.split(' ',1)
		cmd=parts[0]
		try:
			line=parts[1].strip()
		except IndexError:
			line=''
		#试着查找处理程序:
		meth=getattr(self,'do_'+cmd,None)
		try:
			#假定它是可调用的:
			meth(session,line)
		except TypeError:
			#如果不可以被调用，此段代码响应未知命令
			self.unknown(session,cmd)

class Room(CommandHandler):
	"""
	包括一个或多个用户(会话)的泛型环境。它负责基本的命令处理和广播
	"""

	def __init__(self,server):
		self.server=server
		self.sessions=[]

	def add(self,session):
		'一个会话(用户)已进入房间'
		self.sessions.append(session)

	def remove(self,session):
		'一个会话(用户)已离开房间'
		self.sessions.remove(session)

	def broadcast(self,line):
		'向房间中的所有会话发送一行'
		for session in self.sessions:
			session.push(line)

	def do_logout(self,session,line):
		'响应logout命令'
		raise EndSession

class LoginRoom(Room):
	"""
	为刚刚连接上的用户准备的房间
	"""
	def add(self,session):
		Room.add(self,session)
		#当用户进入时，发出问候
		self.broadcast('Welcome to %s\r\n' % self.server.name)

	def unknown(self,session,cmd):
		#所有未知命令 (除了login或者logout外的一切)
		#会导致一个警告:
		session.push('Please log in\nUse "login <nick>"\r\n')

	def do_login(self,session,line):
		name=line.strip()
		#确保用户输入了名字:
		if not name:
			session.push('Please enter a name\r\n')
		#确保用户名没有被使用:
		elif name in self.server.users:
			session.push('The name "%s" is taken.\r\n' % name)
			session.push('Please try again.\r\n')
		else:
			#名字没问题，所以存储在会话中，并且
			#将用户移动到主聊天室里。
			session.name=name
			session.enter(self.server.main_room)

class ChatRoom(Room):
	"""
	为多用户相互聊天准备的房间
	"""

	def add(self,session):
		#告诉所有人有新用户进入
		self.broadcast(session.name+' has entered the room.\r\n')
		self.server.users[session.name]=session
		Room.add(self,session)
	
	def remove(self,session):
		#告诉所有人有用户离开
		Room.remove(self,session)
		self.broadcast(session.name+' has left the room.\r\n')
	
	def do_say(self,session,line):
		self.broadcast(session.name+': '+line+'\r\n')
	
	def do_look(self,session,line):
		'处理look命令，该命令被用于查看谁在房间内'
		session.push('The following are in this room:\r\n')
		for other in self.sessions:
			session.push(other.name+'\r\n')

	def do_who(self,session,line):
		'处理who命令，该命令被用于查看谁登录了'
		session.push('The following are logged:\r\n')
		for name in self.server.users:
			session.push(name+'\r\n')

	def do_help(self,session,line):
		'处理help命令，该命令用来打印帮助信息'
		session.push('*'*15+'\r\n')
		session.push('Here is the help information:\r\n')
		session.push('Use "say <line>" to chat.\r\n')
		session.push('Use "who" to find logged users.\r\n')
		session.push('Use "look" to find users in this room.\r\n')
		session.push('Use "logout" to logout the chatroom.\r\n')
		session.push('*'*15+'\r\n')

class LogoutRoom(Room):
	"""
	为单用户准备的简单房间。只用于将用户名从服务器移除。
	"""

	def add(self,session):
		#当会话(用户)进入要删除的LogoutRoom时
		try:
			del self.server.users[session.name]
		except KeyError:
			pass

class ChatSession(async_chat):
	"""
	单会话，负责和单用户通信。
	"""

	def __init__(self,server,sock):
		async_chat.__init__(self,sock)
		self.server=server
		self.set_terminator("\r\n")
		self.data=[]
		self.name=None
		#所有的会话都开始于单独的LoginRoom中:
		self.enter(LoginRoom(server))

	def enter(self,room):
		#从当前房间移除自身(self),并且将自身添加到
		#下一个房间...
		try:
			cur=self.room
		except AttributeError:
			pass
		else:
			cur.remove(self)
		self.room=room
		room.add(self)
	
	def collect_incoming_data(self,data):
		self.data.append(data)

	def found_terminator(self):
		line=''.join(self.data)
		self.data=[]
		try:
			self.room.handle(self,line)
		except EndSession:
			self.handle_close()
	
	def handle_close(self):
		async_chat.handle_close(self)
		self.enter(LogoutRoom(self.server))

class ChatServer(dispatcher):
	"""
	只有一个房间的聊天服务器。
	"""
	
	def __init__(self,port,name):
		dispatcher.__init__(self)
		self.create_socket(socket.AF_INET,socket.SOCK_STREAM)
		self.set_reuse_addr()
		self.bind(('',port))
		self.listen(5)
		self.name=name
		self.users={}
		self.main_room=ChatRoom(self)

	def handle_accept(self):
		conn,addr=self.accept()
		print 'Get connection:%s:%s' %(addr[0],addr[1])
		ChatSession(self,conn)

if __name__=='__main__':
	s=ChatServer(PORT,NAME)
	try:
		asyncore.loop()
	except KeyboardInterrupt:
		print

