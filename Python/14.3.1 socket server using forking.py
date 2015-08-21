from SocketServer import TCPServer,StreamRequestHandler,ForkingMixIn

class Server(ForkingMixIn,TCPServer):pass

class Handler(StreamRequestHandler):

	def handle(self):
		addr=self.request.getpeername()
		print 'Got connection from',addr
		self.wfile.write('Thank you for connecting')

server=TCPServer(('',1234),Handler)
server.serve_forever()

