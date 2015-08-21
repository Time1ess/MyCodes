import socket

s=socket.socket()
host=socket.gethostname()
port=1234

s.connect((host,port))
while True:
	message=raw_input('Enter message:')
	if message=='exit':
		break
	s.send(message)

