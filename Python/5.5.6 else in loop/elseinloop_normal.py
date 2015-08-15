from math import sqrt
#for...else
broke_out=False
for n in range(99,81,-1):
	root=sqrt(n)
	if root==int(root):
		print n
		broke_out=True
		break
if not broke_out:
	print 'Didn\'t find it!'
