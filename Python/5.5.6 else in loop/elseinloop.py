from math import sqrt
#for...else
for n in range(99,81,-1):
	root=sqrt(n)
	if root==int(root):
		print n
		break
else:
	print 'Didn\'t find it!'
