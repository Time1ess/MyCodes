try:
	1/0
except:
	print 'Catch exception!'
else:
	print 'That went well!'
finally:
	print 'Cleaning up.'

#Notice: When a exception raised,the respond level goes like this:self except
# block(if exists)>self finally block(if exists)>Upper layer except block>...
# >top layer except block
