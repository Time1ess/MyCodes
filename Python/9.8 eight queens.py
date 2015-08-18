def conflict(state,nextX):
	nextY=len(state)
	for i in range(nextY):
		if abs(state[i]-nextX) in (0,nextY-i):
			return True
	return False
#It is true if the horizontal distance between the next
#queen and the previous one under consideration is either
#zero (same column) or equal to the vertical distance(on a
#diagonal).Otherwise,it if false

def queens(num=8,state=()):
	for pos in range(num):
		if not conflict(state,pos):
			if len(state)==num-1:
				yield (pos,)
			else:
				for result in queens(num,state+(pos,)):
					yield (pos,)+result

def prettyprint(solution):
	def line(pos,length=len(solution)):
		return '.'*(pos)+'X'+'.'*(length-pos-1)
	for pos in solution:
		print line(pos)

for solution in queens(8):
	print solution
index=1
print ''
for solution in queens(8):
	print index
	print ''
	prettyprint(solution)
	print ''
	index+=1
	if index>5:
		break
print 'Total:',len(list(queens(8)))


