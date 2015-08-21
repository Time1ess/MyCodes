import socket,select

s=socket.socket()

host=socket.gethostname()
port=1234
s.bind((host,port))

s.listen(5)
inputs=[s]
while True:
	rs,ws,es=select.select(inputs,[],[])
	#select:three arguments(the fourth `timeout` is optional),
	#the first is rlist:wait until ready for reading
	#the seconde is wlist:wait until ready for writing
	#the third is xlist:wait for an "exceptional condition"
	#if one of the list is ready or reach timeout,
	#The return value is a triple of lists of objects:
	#subsets of the first three arguments
	

	#in this case,rs is a subset of inputs, which means server
	#or clients
	for r in rs:	
		if r is s:		#if r is server,indicates a new connection 
			c,addr=s.accept()
			print 'Got connection from',addr
			inputs.append(c)
		else:		#if r is client,indicates new data
			try:
				data=r.recv(1024)
				disconnected=not data
			except socket,error:
				disconnected=True

			if disconnected:
				print r.getpeername(),'disconnected'
				inputs.remove(r)
			else:
				print data
